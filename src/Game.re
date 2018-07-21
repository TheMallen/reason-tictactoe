open SharedTypes;

let component = ReasonReact.reducerComponent("Game");

let initialState = {
  board: [
    [Empty, Empty, Empty],
    [Empty, Empty, Empty],
    [Empty, Empty, Empty],
  ],
  gameState: Playing(X),
};

let updateBoard = (
  board: board,
  gameState: gameState,
  position
) => {
  let (rowPos, columnPos) = position;

  board |> List.mapi((xIndex: int, row: row) => {
    row |> List.mapi((yIndex: int, value: field) => {
      if (rowPos == xIndex && columnPos == yIndex) {
        switch (gameState, value) {
        | (_, Marked(_)) => value
        | (Playing(player), Empty) => Marked(player)
        | (_, Empty) => Empty
        }
      } else {
        value;
      }
    });
  });
};

let checkRow = (
  player: player,
  position: point,
  board: board
) => {
  let (rowPos, _) = position;
  let row = rowPos |> List.nth(board);

  row |> List.fold_left((accumulator, field: field) => {
    accumulator && field == Marked(player)
  }, true);
};

let checkColumn = (
  player: player,
  position: point,
  board: board
) => {
  let (_, colPos) = position;

  board |> List.fold_left((accumulator, row: row) => {
    let field = colPos |> List.nth(row);
    accumulator && field == Marked(player);
  }, true);
};

let checkDiagonal = (
  player: player,
  position: point,
  board: board
) => {
  false
};

let checkStalemate = (
  _board: board
) => {
  false;
};

let checkMove = (
  player: player,
  position: point,
  board: board,
) => {
  checkRow(player, position, board) ||
  checkDiagonal(player, position, board) ||
  checkColumn(player, position, board);
};

let nextPlayer = (player: player) => switch(player) {
  | X => O
  | O => X
};

let nextGameState = (
  player: player,
  position: point,
  board: board
) => {
  let win = checkMove(player, position, board);

  if (win) {
    Winner(player);
  } else {
    let draw = checkStalemate(board);
    if (draw) Draw else Playing(nextPlayer(player));
  }
};

let updateGameState = (
  board: board,
  position: point,
  gameState: gameState,
) => {
  switch(gameState) {
  | Playing(X) => nextGameState(X, position, board)
  | Playing(O) => nextGameState(O, position, board)
  | _ => gameState
  }
};

let make = _children => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) => {
    switch (action) {
    | Restart => {
        Js.log("restarting");
        ReasonReact.Update(initialState);
      }
    | ClickSquare((position: point)) => {
        Js.log({j| clicked $(position) |j});
        let {board, gameState} = state;

        let nextBoard = updateBoard(
          board,
          gameState,
          position,
        );

        let nextGameState = updateGameState(
          nextBoard,
          position,
          gameState,
        );

        ReasonReact.Update({
          board: nextBoard,
          gameState: nextGameState,
        });
      }
    }
  },
  render: ({state: state, send}) => {
    <div className="Game">
      <Board
        state
        onMark=(id => send(ClickSquare(id)))
      />

      <Message gameState=(state.gameState) />

      <button
        className="Button"
        onClick=((_e) => send(Restart))
      >
        <Text>"Restart"</Text>
      </button>
    </div>
  },
};

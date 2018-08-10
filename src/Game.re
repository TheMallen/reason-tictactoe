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

let winPositions = [
  [(0, 2), (1, 2), (2, 2)],
  [(0, 1), (1, 1), (2, 1)],
  [(0, 0), (0, 1), (0, 2)],
  [(2, 0), (2, 1), (2, 2)],
  [(1, 0), (1, 1), (1, 2)],
  [(0, 0), (0, 1), (0, 2)],
  [(0, 0), (1, 1), (2, 2)],
  [(2, 0), (1, 1), (0, 2)],
];

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

let getField(board: board, pos: point) = {
  let (rowPos, colPos) = pos;
  colPos |> (List.nth(board, rowPos) |> List.nth);
};

let checkBoardIsWon = (combinations: list(list(point)), player: player, board: board, ) => {
  combinations |> List.fold_left((accumulator: bool, combination: list(point)) => {
    accumulator && combination |> List.fold_left((accumulator: bool, pos: point) => {
      let field = getField(board, pos);
      accumulator && field == Marked(player);
    }, true);
  }, true);
};

let checkBoardIsWon3x3 = checkBoardIsWon(winPositions);

let nextPlayer = (player: player) => switch(player) {
  | X => O
  | O => X
};

let nextGameState = (
  player: player,
  board: board
) => {
  let win = checkBoardIsWon3x3(player, board);

  if (win) {
    Winner(player);
  } else {
    let draw = false; /* checkStalemate(board); */
    if (draw) Draw else Playing(nextPlayer(player));
  }
};

let updateGameState = (
  board: board,
  gameState: gameState,
) => {
  switch(gameState) {
  | Playing(X) => nextGameState(X, board)
  | Playing(O) => nextGameState(O, board)
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

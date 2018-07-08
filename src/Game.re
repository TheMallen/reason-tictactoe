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

  let (xPos, yPos) = position;

  board |> List.mapi((xIndex: int, row: row) => {
    row |> List.mapi((yIndex: int, value: field) => {
      if (xPos == xIndex && yPos == yIndex) {
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

let updateGameState = (
  _nextBoard: board,
  _board: board,
  gameState: gameState,
) => {
  gameState;
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
          Js.log({j|clicked $(position)|j});
          let {board, gameState} = state;

          let nextBoard = updateBoard(
            board,
            gameState,
            position,
          );

          let nextGameState = updateGameState(
            nextBoard,
            board,
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
      <button
        className="Button"
        onClick=((_e) => send(Restart))
      >
        <Text>"Restart"</Text>
      </button>
    </div>
  },
};

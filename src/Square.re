open SharedTypes;

let component = ReasonReact.statelessComponent("Square");

let getClass = (gameState, value) => {
  switch (gameState) {
    | Winner(value) => "Square--green"
    | other => "Square"
  }
};

let isFinished = (gameState) => {
  switch (gameState) {
    | Winner(X) => true
    | Winner(O) => true
    | other => false
  }
};

let toValue = (field: field) => {
  switch (field) {
    | Marked(X) => "X"
    | Marked(O) => "O"
    | Empty => ""
  }
};

let make = (
  ~value: field,
  ~gameState: gameState,
  ~onMark,
  _children
) => {
  ...component,
  render: _self => {
    <button
      className=(getClass(gameState, value))
      disabled=(
        gameState
          |> isFinished
          |> Js.Boolean.to_js_boolean
      )
      onClick=(_evt => onMark())
    >
      <Text>(value |> toValue)</Text>
    </button>
  }
};

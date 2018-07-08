open SharedTypes;

let component = ReasonReact.statelessComponent("Board");

let make = (
  ~gameState: gameState,
  _children,
) => {
  ...component,
  render: _ =>
    <p className="Message">
      <Text>
      (
        switch (gameState) {
        | Playing(X) => "X's turn"
        | Playing(O) => "O's turn"
        | Winner(X) => "X wins! ✨🎉"
        | Winner(O) => "O wins! ✨🎉"
        | Draw => "🐈's game!"
        }
      )
      </Text>
    </p>,
};

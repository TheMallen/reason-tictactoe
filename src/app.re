[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");

let str = ReasonReact.stringToElement;

let make = (_children) => {
  ...component,
  render: (_self) => {
    <div className="App">
      <header className="App-header">
        <h2>
          <Text>"Tic Tac Toe"</Text>
        </h2>
      </header>
      <Game />
    </div>
  },
};

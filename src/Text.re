let component = ReasonReact.statelessComponent("Text");

let make = (children: array(string)) => {
  ...component,
  render: (_self) => {
    ReasonReact.stringToElement(children[0])
  }
};

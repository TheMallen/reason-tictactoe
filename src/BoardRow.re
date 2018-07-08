open SharedTypes;

let component = ReasonReact.statelessComponent("BoardRow");

let make = (~gameState: gameState, ~row: row, ~onMark, ~index: int, _children) => {
   ...component,
   render: (_) =>
    <div className="board-row">
      (
        row
        |> List.mapi((ind: int, value: field) => {
            let id = string_of_int(index) ++ string_of_int(ind);
            let coordinates = (index, ind);

            <Square
              value
              gameState
              key=id
              onMark=(() => onMark(coordinates))
            />
          })
        |> Array.of_list
        |> ReasonReact.arrayToElement
      )
  </div>,
};

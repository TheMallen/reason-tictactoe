open SharedTypes;

let component = ReasonReact.statelessComponent("BoardRow");

let make = (~gameState: gameState, ~row: row, ~onMark, ~colIndex: int, _children) => {
   ...component,
   render: (_) =>
    <div className="Board-row">
      (
        row
        |> List.mapi((rowIndex: int, value: field) => {
            let id = string_of_int(rowIndex) ++ string_of_int(rowIndex);
            let coordinates = (colIndex, rowIndex);

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

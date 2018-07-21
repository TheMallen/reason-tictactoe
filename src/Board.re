open SharedTypes;

let component = ReasonReact.statelessComponent("Board");

let make = (
  ~state: state,
  ~onMark,
  _children
) => {
  ...component,
  render: _ =>
    <div className="Board">
    (
      state.board
        |> List.mapi(
          (colIndex: int, row: row) =>
            <BoardRow
              key=(string_of_int(colIndex))
              gameState=state.gameState
              row
              onMark
              colIndex
            />
        )
        |> Array.of_list
        |> ReasonReact.arrayToElement
    )
    </div>,
};

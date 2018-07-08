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
          (index: int, row: row) =>
            <BoardRow
              key=(string_of_int(index))
              gameState=state.gameState
              row
              onMark
              index
            />
        )
        |> Array.of_list
        |> ReasonReact.arrayToElement
    )
    </div>,
};

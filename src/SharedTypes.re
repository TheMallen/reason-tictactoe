type point = (int, int);

type player =
  | X
  | O;

type field =
  | Empty
  | Marked(player);

type gameState =
  | Playing(player)
  | Winner(player)
  | Draw;

type row = list(field);
type board = list(row);

type action =
  | ClickSquare(point)
  | Restart;

type state = {
  board,
  gameState,
}

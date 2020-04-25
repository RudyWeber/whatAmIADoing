include Belt.Result;

let fold = (f, g) =>
  fun
  | Ok(x) => f(x)
  | Error(x) => g(x);

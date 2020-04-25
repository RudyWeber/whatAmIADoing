// natural transformation Either -> Task
let resultToTask = e => e |> Result.fold(Task.of_, Task.reject);

// Task(Result(a, b), b) -> Task(f(a), b)
let fmap = (task, f) => {
  Task.bind(task, resultToTask)->Task.map(f);
};

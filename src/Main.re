let program = Db.getData(10)->ResultTask.fmap(x => x.value);

program->Task.fork(
  x => Js.Console.error2("Oh no:", x),
  x => Js.Console.log2("Got:", x),
);

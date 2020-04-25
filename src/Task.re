type cb('a, 'd) = 'a => 'd;

type task('b, 'c) = {. fork: (cb('b, unit), cb('c, unit)) => unit};

let make = computation => {
  let t: task('a, 'b) = {
    as _;
    pub fork = (rej, res) => computation(rej, res)
  };
  t;
};

let of_ = value => make((_, res) => res(value));

let reject = value => make((rej, _) => rej(value));

let map = (t, cb) =>
  make((rej, res) => t#fork(rej, value => res(cb(value))));

let bind = (t, f) =>
  make((rej, res) => t#fork(rej, x => f(x)#fork(rej, res)));

let join = bind(_, x => x);

let fork = (t, rej, res) => {
  t#fork(rej, res);
};

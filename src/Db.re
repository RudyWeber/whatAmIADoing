type data = {
  id: int,
  value: string,
};

let decodeData = d =>
  Json.Decode.{
    id: d |> field("id", int),
    value: d |> field("value", string),
  };

let getData = id =>
  FetchTask.fetch(
    ~path="http://localhost:3000/data/" ++ string_of_int(id),
    ~decodeResponseOk=decodeData,
    (),
  );

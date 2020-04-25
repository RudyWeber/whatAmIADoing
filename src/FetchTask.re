[@bs.module "node-fetch"]
external fetch: string => Js.Promise.t('a) = "default";

type error = {message: string};

let decodeError = e => Json.Decode.{message: e |> field("message", string)};
let getErrorMessage = e => e.message;

let fetch = (~path, ~decodeResponseOk, ()) =>
  Task.make((rej, res) => {
    fetch(path)
    |> Js.Promise.then_(response => {
         let statusCode = response->Fetch.Response.status;
         if (statusCode >= 500) {
           rej(response->Fetch.Response.statusText);
           Js.Promise.reject(failwith(Fetch.Response.statusText(response)));
         } else {
           response->Fetch.Response.json
           |> Js.Promise.then_(value => {
                if (statusCode >= 200 && statusCode < 300) {
                  res(Result.Ok(value |> decodeResponseOk));
                } else if (statusCode >= 300 && statusCode < 500) {
                  res(Result.Error(value |> decodeError |> getErrorMessage));
                };
                Js.Promise.resolve();
              });
         };
       })
    |> Js.Promise.catch(err => {
         let rejectionMessage =
           err->Js.Json.stringifyAny->Belt.Option.getWithDefault("");
         rej(rejectionMessage);
         Js.Promise.reject(failwith(rejectionMessage));
       })
    |> ignore
  });

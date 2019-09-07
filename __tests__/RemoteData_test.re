// test dont work yet.
open Jest;

open Expect;

type messageOk = string;
type messageLoading = string;
type messageError = string;
type t = RemoteData.t(messageOk, messageError);

describe("RemoteData", () => {
  describe("NotAsked", () => {
    let actual = RemoteData.NotAsked;
    test("isNotAsked to be true", () =>
      actual |> RemoteData.isNotAsked |> expect |> toBe(true)
    );
    test("isLoading to be false", () =>
      actual |> RemoteData.isLoading |> expect |> toBe(false)
    );
    test("isSuccess to be false", () =>
      actual |> RemoteData.isSuccess |> expect |> toBe(false)
    );
    test("isFailure to be false", () =>
      actual |> RemoteData.isFailure |> expect |> toBe(false)
    );
  });
  describe("Loading('p)", () => {
    let actual = RemoteData.Loading;
    test("isNotAsked to be false", () =>
      actual |> RemoteData.isNotAsked |> expect |> toBe(false)
    );
    test("isLoading to be true", () =>
      actual |> RemoteData.isLoading |> expect |> toBe(true)
    );
    test("isSuccess to be false", () =>
      actual |> RemoteData.isSuccess |> expect |> toBe(false)
    );
    test("isFailure to be false", () =>
      actual |> RemoteData.isFailure |> expect |> toBe(false)
    );
  });
  describe("Success('a)", () => {
    let actual = RemoteData.Success("");
    test("isNotAsked to be false", () =>
      actual |> RemoteData.isNotAsked |> expect |> toBe(false)
    );
    test("isLoading to be false", () =>
      actual |> RemoteData.isLoading |> expect |> toBe(false)
    );
    test("isSuccess to be true", () =>
      actual |> RemoteData.isSuccess |> expect |> toBe(true)
    );
    test("isFailure to be false", () =>
      actual |> RemoteData.isFailure |> expect |> toBe(false)
    );
  });
  describe("Failure('e)", () => {
    let actual = RemoteData.Failure("");
    test("isNotAsked to be false", () =>
      actual |> RemoteData.isNotAsked |> expect |> toBe(false)
    );
    test("isLoading to be false", () =>
      actual |> RemoteData.isLoading |> expect |> toBe(false)
    );
    test("isSuccess to be false", () =>
      actual |> RemoteData.isSuccess |> expect |> toBe(false)
    );
    test("isFailure to be true", () =>
      actual |> RemoteData.isFailure |> expect |> toBe(true)
    );
  });
  describe("andMap", () => {
    test("Success", () =>
      RemoteData.andMap(
        RemoteData.Success("before"),
        RemoteData.Success(before => before ++ " after"),
      )
      |> expect
      |> toEqual(RemoteData.Success("before after"))
    );
    test("Failure before", () =>
      RemoteData.andMap(RemoteData.Failure("before"), RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.Failure("before"))
    );
    test("Failure after", () =>
      RemoteData.andMap(RemoteData.NotAsked, RemoteData.Failure("after"))
      |> expect
      |> toEqual(RemoteData.Failure("after"))
    );
    test("Loading before", () =>
      RemoteData.andMap(RemoteData.Loading, RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.Loading)
    );
    test("Loading after", () =>
      RemoteData.andMap(RemoteData.NotAsked, RemoteData.Loading)
      |> expect
      |> toEqual(RemoteData.Loading)
    );
    test("NotAsked before", () =>
      RemoteData.andMap(
        RemoteData.NotAsked,
        RemoteData.Success(before => before ++ " after"),
      )
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
    test("NotAsked after", () =>
      RemoteData.andMap(RemoteData.Success("before"), RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("map", () => {
    let mapper = before => before ++ " after";
    test("Success", () =>
      RemoteData.map(mapper, RemoteData.Success("before"))
      |> expect
      |> toEqual(RemoteData.Success("before after"))
    );
    test("Failure", () =>
      RemoteData.map(mapper, RemoteData.Failure("failure"))
      |> expect
      |> toEqual(RemoteData.Failure("failure"))
    );
    test("Loading", () =>
      RemoteData.map(mapper, RemoteData.Loading)
      |> expect
      |> toEqual(RemoteData.Loading)
    );
    test("NotAsked", () =>
      RemoteData.map(mapper, RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("map2", () => {
    let mapper = (before1, before2) => before1 ++ " " ++ before2 ++ " after";
    test("Success", () =>
      RemoteData.map2(
        mapper,
        RemoteData.Success("before1"),
        RemoteData.Success("before2"),
      )
      |> expect
      |> toEqual(RemoteData.Success("before1 before2 after"))
    );
    test("Failure - first", () =>
      RemoteData.map2(
        mapper,
        RemoteData.Failure("failure1"),
        RemoteData.Failure("failure2"),
      )
      |> expect
      |> toEqual(RemoteData.Failure("failure1"))
    );
    test("Failure - second", () =>
      RemoteData.map2(
        mapper,
        RemoteData.Success("failure1"),
        RemoteData.Failure("failure2"),
      )
      |> expect
      |> toEqual(RemoteData.Failure("failure2"))
    );
    test("Loading - first", () =>
      RemoteData.map2(mapper, RemoteData.Loading, RemoteData.Loading)
      |> expect
      |> toEqual(RemoteData.Loading)
    );
    test("Loading - second", () =>
      RemoteData.map2(
        mapper,
        RemoteData.Success("loading1"),
        RemoteData.Loading,
      )
      |> expect
      |> toEqual(RemoteData.Loading)
    );
    test("NotAsked - first", () =>
      RemoteData.map2(mapper, RemoteData.NotAsked, RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
    test("NotAsked - second", () =>
      RemoteData.map2(
        mapper,
        RemoteData.Success("notAsked1"),
        RemoteData.NotAsked,
      )
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("map3", () => {
    let mapper = (before1, before2, before3) =>
      before1 ++ " " ++ before2 ++ " " ++ before3 ++ " after";
    test("Success", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("before1"),
        RemoteData.Success("before2"),
        RemoteData.Success("before3"),
      )
      |> expect
      |> toEqual(RemoteData.Success("before1 before2 before3 after"))
    );
    test("Failure - first", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Failure("failure1"),
        RemoteData.Failure("failure2"),
        RemoteData.Failure("failure3"),
      )
      |> expect
      |> toEqual(RemoteData.Failure("failure1"))
    );
    test("Failure - second", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("failure1"),
        RemoteData.Failure("failure2"),
        RemoteData.Failure("failure3"),
      )
      |> expect
      |> toEqual(RemoteData.Failure("failure2"))
    );
    test("Failure - third", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("failure1"),
        RemoteData.Success("failure2"),
        RemoteData.Failure("failure3"),
      )
      |> expect
      |> toEqual(RemoteData.Failure("failure3"))
    );
    test("Loading - first", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Loading,
        RemoteData.Loading,
        RemoteData.Loading,
      )
      |> expect
      |> toEqual(RemoteData.Loading)
    );
    test("Loading - second", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("loading1"),
        RemoteData.Loading,
        RemoteData.Loading,
      )
      |> expect
      |> toEqual(RemoteData.Loading)
    );
    test("Loading - third", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("loading1"),
        RemoteData.Success("loading2"),
        RemoteData.Loading,
      )
      |> expect
      |> toEqual(RemoteData.Loading)
    );
    test("NotAsked - first", () =>
      RemoteData.map3(
        mapper,
        RemoteData.NotAsked,
        RemoteData.NotAsked,
        RemoteData.NotAsked,
      )
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
    test("NotAsked - second", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("notAsked1"),
        RemoteData.NotAsked,
        RemoteData.NotAsked,
      )
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
    test("NotAsked - third", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("notAsked1"),
        RemoteData.Success("notAsked2"),
        RemoteData.NotAsked,
      )
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("mapError", () => {
    let mapper = before => before ++ " after";
    test("Success", () =>
      RemoteData.mapError(mapper, RemoteData.Success("before"))
      |> expect
      |> toEqual(RemoteData.Success("before"))
    );
    test("Failure", () =>
      RemoteData.mapError(mapper, RemoteData.Failure("before"))
      |> expect
      |> toEqual(RemoteData.Failure("before after"))
    );
    test("Loading", () =>
      RemoteData.mapError(mapper, RemoteData.Loading)
      |> expect
      |> toEqual(RemoteData.Loading)
    );
    test("NotAsked", () =>
      RemoteData.mapError(mapper, RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("mapBoth", () => {
    let successMapper = before => before ++ " after success";
    let errorMapper = before => before ++ " after error";
    test("Success", () =>
      RemoteData.mapBoth(
        successMapper,
        errorMapper,
        RemoteData.Success("before"),
      )
      |> expect
      |> toEqual(RemoteData.Success("before after success"))
    );
    test("Failure", () =>
      RemoteData.mapBoth(
        successMapper,
        errorMapper,
        RemoteData.Failure("before"),
      )
      |> expect
      |> toEqual(RemoteData.Failure("before after error"))
    );
    test("Loading", () =>
      RemoteData.mapBoth(successMapper, errorMapper, RemoteData.Loading)
      |> expect
      |> toEqual(RemoteData.Loading)
    );
    test("NotAsked", () =>
      RemoteData.mapBoth(successMapper, errorMapper, RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("andThen", () => {
    let mapper = before => RemoteData.Failure(before ++ " after");
    test("Success", () =>
      RemoteData.andThen(mapper, RemoteData.Success("before"))
      |> expect
      |> toEqual(RemoteData.Failure("before after"))
    );
    test("Failure", () =>
      RemoteData.andThen(mapper, RemoteData.Failure("before"))
      |> expect
      |> toEqual(RemoteData.Failure("before"))
    );
    test("Loading", () =>
      RemoteData.andThen(mapper, RemoteData.Loading)
      |> expect
      |> toEqual(RemoteData.Loading)
    );
    test("NotAsked", () =>
      RemoteData.andThen(mapper, RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("withDefault", () => {
    test("Success", () =>
      RemoteData.withDefault(
        "got default",
        RemoteData.Success("got success"),
      )
      |> expect
      |> toBe("got success")
    );
    test("Failure", () =>
      RemoteData.withDefault(
        "got default",
        RemoteData.Failure("got failure"),
      )
      |> expect
      |> toBe("got default")
    );
    test("Loading", () =>
      RemoteData.withDefault("got default", RemoteData.Loading)
      |> expect
      |> toBe("got default")
    );
    test("NotAsked", () =>
      RemoteData.withDefault("got default", RemoteData.Loading)
      |> expect
      |> toEqual("got default")
    );
  });
  describe("isSuccess", () => {
    test("Ok", () =>
      RemoteData.isSuccess(Belt.Result.Ok(true))
      |> expect
      |> toEqual(RemoteData.Success(true))
    );
    test("Error", () =>
      RemoteData.isSuccess(Belt.Result.Error("from result"))
      |> expect
      |> toEqual(RemoteData.Failure("from result"))
    );
  });
  describe("toOption", () => {
    test("Success", () =>
      RemoteData.toOption(RemoteData.Success("got success"))
      |> expect
      |> toEqual(Some("got success"))
    );
    test("Failure", () =>
      RemoteData.toOption(RemoteData.Failure("got failure"))
      |> expect
      |> toEqual(None)
    );
    test("Loading", () =>
      RemoteData.toOption(RemoteData.Loading) |> expect |> toEqual(None)
    );
    test("NotAsked", () =>
      RemoteData.toOption(RemoteData.NotAsked) |> expect |> toEqual(None)
    );
  });
  describe("append", () => {
    test("Success(a) + Success(b) = Success((a, b))", () =>
      RemoteData.append(RemoteData.Success("a"), RemoteData.Success("b"))
      |> expect
      |> toEqual(RemoteData.Success(("a", "b")))
    );
    test("Failure(a) + Success(b) = Failure(a)", () =>
      RemoteData.append(RemoteData.Failure("a"), RemoteData.Success("b"))
      |> expect
      |> toEqual(RemoteData.Failure("a"))
    );
    test("Success(a) + Failure(b)", () =>
      RemoteData.append(RemoteData.Success("a"), RemoteData.Failure("b"))
      |> expect
      |> toEqual(RemoteData.Failure("b"))
    );
    test("Loading(a) + Success(b) = Loading(a)", () =>
      RemoteData.append(RemoteData.Loading("a"), RemoteData.Success("b"))
      |> expect
      |> toEqual(RemoteData.Loading("a"))
    );
    test("Success(a) + Loading(b) = Loading(b)", () =>
      RemoteData.append(RemoteData.Success("a"), RemoteData.Loading("b"))
      |> expect
      |> toEqual(RemoteData.Loading("b"))
    );
    test("NotAsked + Success(b) = NotAsked", () =>
      RemoteData.append(RemoteData.NotAsked, RemoteData.Success("b"))
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
    test("Success(b) + NotAsked = NotAsked", () =>
      RemoteData.append(RemoteData.Success("b"), RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("succeed", () => {
    test("a => Success(a)", () =>
      RemoteData.succeed("got success")
      |> expect
      |> toEqual(RemoteData.Success("got success"))
    );
    ignore();
  });
  describe("isSuccess", () => {
    test("Success returns true", () =>
      RemoteData.isSuccess(RemoteData.Success("got success"))
      |> expect
      |> toBe(true)
    );
    test("Failure returns false", () =>
      RemoteData.isSuccess(RemoteData.Failure("got failure"))
      |> expect
      |> toBe(false)
    );
    test("Loading returns false", () =>
      RemoteData.isSuccess(RemoteData.Loading) |> expect |> toBe(false)
    );
    test("NotAsked returns false", () =>
      RemoteData.isSuccess(RemoteData.NotAsked) |> expect |> toBe(false)
    );
  });
  describe("isFailure", () => {
    test("Success returns false", () =>
      RemoteData.isFailure(RemoteData.Success("got success"))
      |> expect
      |> toBe(false)
    );
    test("Failure returns true", () =>
      RemoteData.isFailure(RemoteData.Failure("got failure"))
      |> expect
      |> toBe(true)
    );
    test("Loading returns false", () =>
      RemoteData.isFailure(RemoteData.Loading) |> expect |> toBe(false)
    );
    test("NotAsked returns false", () =>
      RemoteData.isFailure(RemoteData.NotAsked) |> expect |> toBe(false)
    );
  });
  describe("isLoading", () => {
    test("Success returns false", () =>
      RemoteData.isLoading(RemoteData.Success("got success"))
      |> expect
      |> toBe(false)
    );
    test("Failure returns false", () =>
      RemoteData.isLoading(RemoteData.Failure("got failure"))
      |> expect
      |> toBe(false)
    );
    test("Loading returns true", () =>
      RemoteData.isLoading(RemoteData.Loading) |> expect |> toBe(true)
    );
    test("NotAsked returns false", () =>
      RemoteData.isLoading(RemoteData.NotAsked) |> expect |> toBe(false)
    );
  });
  describe("isNotAsked", () => {
    test("Success returns false", () =>
      RemoteData.isNotAsked(RemoteData.Success("got success"))
      |> expect
      |> toBe(false)
    );
    test("Failure returns false", () =>
      RemoteData.isNotAsked(RemoteData.Failure("got failure"))
      |> expect
      |> toBe(false)
    );
    test("Loading returns false", () =>
      RemoteData.isNotAsked(RemoteData.Loading) |> expect |> toBe(false)
    );
    test("NotAsked returns true", () =>
      RemoteData.isNotAsked(RemoteData.NotAsked) |> expect |> toBe(true)
    );
  });
});
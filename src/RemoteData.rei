type t('e, 'a) =
  | NotAsked
  | Loading
  | Failure('e)
  | Success('a);

let map: ('a => 'b, t('e, 'a)) => t('e, 'b);

let map2: (('a, 'b) => 'c, t('e, 'a), t('e, 'b)) => t('e, 'c);

let map3:
  (('a, 'b, 'c) => 'd, t('e, 'a), t('e, 'b), t('e, 'c)) =>
  t('e, 'd);

let mapError: ('e => 'f, t('e, 'a)) => t('f, 'a);

let mapBoth: ('a => 'b, 'e => 'f, t('e, 'a)) => t('f, 'b);

let andThen: ('a => t('e, 'b), t('e, 'a)) => t('e, 'b);

let withDefault: ('a, t('e, 'a)) => 'a;

let toOption: t('e, 'a) => option('a);

let fromOption: (option('a), 'e) => t('e, 'a);

let append: (t('e, 'a), t('e, 'b)) => t('e, ('a, 'b));

let andMap: (t('e, 'a), t('e, 'a => 'b)) => t('e, 'b);

let succeed: 'a => t('e, 'a);

let isSuccess: t('e, 'a) => bool;

let isFailure: t('e, 'a) => bool;

let isLoading: t('e, 'a) => bool;

let isNotAsked: t('e, 'a) => bool;
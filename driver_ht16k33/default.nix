{ stdenv, cmake, autoPatchelfHook }:
stdenv.mkDerivation {
  pname = "ht16k33";
  version = "0.0.1";
  src = ./.;
  buildInputs = [ ];
  nativeBuildInputs = [ cmake autoPatchelfHook ];
}

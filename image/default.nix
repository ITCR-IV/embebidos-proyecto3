{ stdenv, opencv, cmake  }:
stdenv.mkDerivation {
  pname = "ompfilters";
  version = "0.0.1";
  src = ./.;
  buildInputs = [ opencv ];
  nativeBuildInputs = [ cmake ];
}

{ stdenv, libmicrohttpd, ompfilters, opencv, cmake }:
stdenv.mkDerivation {
  pname = "Imageserver";
  version = "0.0.1";
  src = ./.;
  buildInputs = [ libmicrohttpd opencv ompfilters ];
  nativeBuildInputs = [ cmake ];
}

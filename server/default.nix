{ stdenv, libmicrohttpd, opencv, cmake }:
stdenv.mkDerivation {
  pname = "Imageserver";
  version = "0.0.1";
  src = ./.;
  buildInputs = [ libmicrohttpd opencv ];
  nativeBuildInputs = [ cmake ];
}

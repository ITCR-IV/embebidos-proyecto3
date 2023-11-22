{ stdenv, i2c-tools, cmake  }:
stdenv.mkDerivation {
  pname = "ht16k33";
  version = "0.0.1";
  src = ./.;
  buildInputs = [ i2c-tools ];
  nativeBuildInputs = [ cmake ];
}

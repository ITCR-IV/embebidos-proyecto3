# TriviOS

Código tomado de: https://git.sr.ht/~fabianmv/triviOS/tree/main/item/triviOS/boot.nix

### Compilación:

```bash
nix build '.#images.pi3' --extra-experimental-features nix-command --extra-experimental-features flakes --show-trace --print-build-logs
```

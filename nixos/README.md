# TriviOS

Código tomado de: https://git.sr.ht/~fabianmv/triviOS/tree/main/item/triviOS/boot.nix

### Compilación:

```bash
nix build '.#images.pi3' --extra-experimental-features nix-command --extra-experimental-features flakes --show-trace --print-build-logs
```

### Flash

Para flashear la imagen en la tarjeta SD primero identifique cuál es el dispositivo de la tarjeta con `lsblk`. Asegúrese que esté desmontada y ejecute:


```
sudo sh -c 'unzstd result/sd-image/<IMAGEN>.img.zst -d -c -q > /dev/<TARJETA SD>
```

# luCifer

Este proyecto es para la Tarea 2 del curso Principios de Sistemas Operativos en el segundo semestre del 2023.

## Requerimientos
- glibc (para [`argp`](https://www.gnu.org/software/libc/manual/html_node/Argp.html))
- Instalar [`libmicrohttpd`](https://www.gnu.org/software/libmicrohttpd/)
- Instalar [`freeimage`](https://freeimage.sourceforge.io/)

Por ejemplo en arch linux:
```
sudo pacman -S libmicrohttpd freeimage
```

## Instalación

Para instalar el servidor como un servicio de `systemd` puede ejecutar
```
make install
```

Esto creará un ejecutable ImageServer en `/usr/bin` y copiará el archivo
ImageServer.service a `/usr/lib/systemd/system/`.
Para que el programa se inicialice en el booteo puede ejecutar:
```
systemctl daemon-reload
systemctl enable ImageServer.service
```

Finalmente no olvide setear el archivo de configuración del servidor en
`/etc/ImageServer/config.conf`

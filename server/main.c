#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <microhttpd.h>

#define PORT 8080
#define MAX_STRING_SIZE 1024  // Definir un tamaño máximo para el string
#define POSTBUFFERSIZE 512    // Tamaño del buffer para los datos POST

struct connection_info_struct {
    FILE *fp;                          // Archivo para guardar la imagen
    char *string_data;                 // Almacenará el string
    int string_size;                   // Tamaño del string
    struct MHD_PostProcessor *post_processor;  // Procesador de POST
};

// Esta función se llama cada vez que se recibe un fragmento de datos POST
static int iterate_post(void *coninfo_cls, enum MHD_ValueKind kind, const char *key,
                        const char *filename, const char *content_type,
                        const char *transfer_encoding, const char *data, 
                        uint64_t off, size_t size) {
    struct connection_info_struct *con_info = coninfo_cls;

    if (0 == strcmp(key, "file")) {
        if (!con_info->fp) {
            // Abre el archivo para escribir
            con_info->fp = fopen(filename, "ab");
            if (!con_info->fp) return MHD_NO;
        }
        if (size > 0) {
            if (!fwrite(data, size, 1, con_info->fp)) return MHD_NO;
        }
    } else if (0 == strcmp(key, "text")) {
        if (off + size > MAX_STRING_SIZE) return MHD_NO; // Prevenir desbordamiento de buffer

        if (!con_info->string_data) {
            con_info->string_data = malloc(MAX_STRING_SIZE);
            if (!con_info->string_data) return MHD_NO;
        }

        memcpy(con_info->string_data + off, data, size);
        con_info->string_size = off + size;
    }



    return MHD_YES;
}

// Llamado al final del proceso POST para limpiar
static void request_completed(void *cls, struct MHD_Connection *connection,
                              void **con_cls, enum MHD_RequestTerminationCode toe) {
    struct connection_info_struct *con_info = *con_cls;

    if (con_info) {
        if (con_info->post_processor) {
            MHD_destroy_post_processor(con_info->post_processor);
            con_info->post_processor = NULL;
        }
        if (con_info->string_data) free(con_info->string_data);
        if (con_info->fp) fclose(con_info->fp);
        free(con_info);
        *con_cls = NULL;
    }
}

// Función para responder a las conexiones
static enum MHD_Result answer_to_connection(void *cls, struct MHD_Connection *connection,
                                            const char *url, const char *method,
                                            const char *version, const char *upload_data,
                                            size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "POST")) return MHD_NO;

    if (NULL == *con_cls) {
        struct connection_info_struct *con_info;

        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info) return MHD_NO;
        con_info->fp = NULL;
        con_info->string_data = NULL;
        con_info->post_processor = MHD_create_post_processor(connection, POSTBUFFERSIZE, iterate_post, (void *)con_info);

        if (NULL == con_info->post_processor) {
            free(con_info);
            return MHD_NO;
        }

        *con_cls = (void *)con_info;

        return MHD_YES;
    }

    struct connection_info_struct *con_info = *con_cls;

    if (0 != *upload_data_size) {
        MHD_post_process(con_info->post_processor, upload_data, *upload_data_size);
        *upload_data_size = 0;
        return MHD_YES;
    } else {
        // Aquí manejas la respuesta final cuando todos los datos han sido recibidos
        const char *page = "<html><body>Imagen y texto recibidos.</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
        enum MHD_Result ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, 
        &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, &request_completed, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar(); // Espera una tecla para terminar

    MHD_stop_daemon(daemon);
    return 0;
}


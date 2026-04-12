#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente 
	// Escribi: "Hola! Soy un log"

	logger = log_create("tp0.log", "Log Inicial", true, LOG_LEVEL_INFO);

	log_info(logger, "Hola! Soy un log");

	log_destroy(logger);

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	config = config_create("cliente.config");	

	if (config == NULL ) {
		abort();
	} else if ( config_has_property( config, "IP") ) {
		ip = config_get_string_value(config, "IP");
	}

	if (config == NULL ) {
		abort();
	} else if ( config_has_property( config, "PUERTO") ) {
		puerto = config_get_string_value(config, "PUERTO");
	}

	if (config == NULL ) {
		abort();
	} else if ( config_has_property( config, "CLAVE") ) {
		valor = config_get_string_value(config, "CLAVE");
	}
	
	// Loggeamos el valor de config

	logger = log_create("tp0.log", "Log de Clave", true, LOG_LEVEL_INFO);

	log_info(logger, valor);
	log_info(logger, ip);
	log_info(logger, puerto);

	//log_destroy(logger);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	if (conexion == -1) {
		logger = log_create("tp0.log", "Log de Error", true, LOG_LEVEL_ERROR);
		log_error(logger, "No se conecto al servidor");
		abort();
	}

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete

	t_paquete* paquete = crear_paquete();

	char * leido;

	while (1) {
		leido = readline("> ");
	if (leido == NULL || leido[0] == '\0' ) {
		free(leido);	
		break;
	} else {
		add_history(leido);
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
		free(leido);
	}
	}

	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger) 
{
	char* leido;

	// La primera te la dejo de yapa
	

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

	logger = log_create("tp0.log", "Log de Consola", true, LOG_LEVEL_INFO);

	while (1) {
		leido = readline("> ");
	if (leido == NULL || leido[0] == '\0' ) {
		free(leido);	
		break;
	} else {
		add_history(leido);
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
		free(leido);
	}
	}

	log_destroy(logger);

	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
	t_log* logger;

	// Leemos y esta vez agregamos las lineas al paquete

	logger = iniciar_logger();
	logger = log_create("tp0.log", "Log de Paquete", true, LOG_LEVEL_INFO);

	while (1) {
		leido = readline("> ");
	if (leido == NULL || leido[0] == '\0' ) {
		free(leido);	
		break;
	} else {
		add_history(leido);
		log_info(logger, leido);

		//agregar_a_paquete(paquete, leido, strlen(leido) + 1 );

		free(leido);
	}
	}

	log_destroy(logger);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	//config_destroy(config);
	//log_destroy(logger);
	liberar_conexion(conexion);

}

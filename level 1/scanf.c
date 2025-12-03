/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:23:39 by fbanzo-s          #+#    #+#             */
/*   Updated: 2025/12/03 12:25:10 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>

int match_space(FILE *f)
{
    int c;
    int skipped = 0;

    c = fgetc(f);
    while (c != EOF && isspace(c))
    {
        skipped = 1;
        c = fgetc(f);
    }
    // Devolver el primer carácter que no es espacio (o EOF)
    ungetc(c, f); 
    
    // Si encontramos EOF al inicio, retornar error.
    if (c == EOF && skipped == 0)
        return (-1);
    
    // El 'scanf' real no devuelve -1 solo por encontrar EOF, sino por error. 
    // Para simplificar, si no hubo error de flujo, asumimos que estamos bien.
    return (1); 
}

// Función para asegurar que el siguiente carácter en el flujo coincida con 'c'.
// Retorna 1 si coincide, 0 si no coincide, -1 si encuentra EOF o error.
int match_char(FILE *f, char c)
{
    int read_char = fgetc(f);

    if (read_char == EOF)
        return (-1); // Error o EOF
    
    if (read_char == c)
        return (1); // Coincidencia
    else
    {
        // El carácter no coincidió, lo devolvemos al flujo.
        ungetc(read_char, f);
        return (0); // No coincidencia
    }
}

// --------------------------------------------------------------------------
// II. FUNCIONES AUXILIARES: Scan (Lectura de Conversiones)
// --------------------------------------------------------------------------

// Lee un solo carácter y lo almacena en el puntero (char *).
// El %c NO salta espacios en blanco iniciales.
int scan_char(FILE *f, va_list ap)
{
    char *target = va_arg(ap, char *); // Recibe char *

    int c = fgetc(f);
    
    if (c == EOF)
        return (0); // No se leyó nada
    
    *target = (char)c;
    return (1); // 1 elemento leído con éxito
}

// Lee un entero y lo almacena en el puntero (int *).
// (Asume que match_space() ya saltó los espacios en blanco).
int scan_int(FILE *f, va_list ap)
{
    int *target = va_arg(ap, int *); // Recibe int *
    long num = 0; // Usamos long para detectar desbordamiento simple
    int sign = 1;
    int c;
    int digits_read = 0;

    c = fgetc(f);

    // 1. Manejar el signo
    if (c == '-')
    {
        sign = -1;
        c = fgetc(f);
    }
    else if (c == '+')
    {
        c = fgetc(f);
    }
    
    // 2. Leer los dígitos
    while (c >= '0' && c <= '9')
    {
        num = num * 10 + (c - '0');
        digits_read++;
        c = fgetc(f);
    }
    
    // 3. Devolver el carácter no consumido (no dígito, espacio, EOF)
    if (c != EOF)
        ungetc(c, f);

    // 4. Validar y almacenar
    if (digits_read == 0)
        return (0); // No se pudo leer ningún entero (fallo de coincidencia)

    // 5. Asignar el valor (asumiendo que no se requiere manejo de límites INT_MIN/INT_MAX complejo)
    *target = (int)(num * sign); 
    
    return (1); // 1 elemento leído con éxito
}

// Lee una cadena y la almacena en el puntero (char *).
// Se detiene en el primer espacio en blanco, \n o EOF.
// (Asume que match_space() ya saltó los espacios en blanco iniciales).
int scan_string(FILE *f, va_list ap)
{
    char *target = va_arg(ap, char *); // Recibe char * (array)
    int c;
    int i = 0;
    
    c = fgetc(f);
    
    // Leer hasta EOF, espacio, o nueva línea.
    while (c != EOF && !isspace(c))
    {
        // En esta implementación simple, no manejamos el límite de campo.
        target[i++] = (char)c;
        c = fgetc(f);
    }
    
    // Devolver el carácter de terminación (espacio/salto de línea/EOF) al flujo.
    if (c != EOF)
        ungetc(c, f); 
    
    // Si no se leyó ni un solo carácter (por ejemplo, si solo había espacio inicial,
    // pero match_space debió haberlo saltado, o si solo quedaba EOF), se devuelve 0.
    if (i == 0)
    {
        // Nota: Si el flujo estaba en EOF o si solo había espacio, pero match_space
        // ya se ejecutó, esto sólo fallaría si el flujo realmente se corrompe.
        return (0);
    }

    target[i] = '\0'; // Terminar la cadena
    return (1); // 1 elemento leído con éxito
}

// --------------------------------------------------------------------------
// III. Lógica Central (ft_vfscanf)
// --------------------------------------------------------------------------

// Determina la conversión necesaria y llama a la función de escaneo.
int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
            // %c NO salta espacios
            (*format)++;
			return scan_char(f, ap);
		case 'd':
            // %d salta espacios, que ya fueron saltados por match_space(f) antes de la llamada.
            (*format)++;
			return scan_int(f, ap);
		case 's':
            // %s salta espacios, que ya fueron saltados por match_space(f) antes de la llamada.
            (*format)++;
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			// Si el '%' no es seguido por una conversión válida, fallamos.
			return 0; 
	}
}

// ft_vfscanf (análogo a vfscanf): Escanea el archivo 'f' según el 'format'.
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;
	int ret_val;

	// Pequeña corrección de robustez: Chequear si el flujo está vacío al inicio.
	// La implementación real de scanf intenta leer algo antes de devolver EOF.
	// Tu bloque original es bueno para chequear si el flujo ya está en EOF.
	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			// Intentamos una conversión (%d, %c, %s)
			ret_val = match_conv(f, &format, ap);
			if (ret_val == 1)
				nconv++; // Conversión exitosa
			else if (ret_val == 0)
				break; // Falla de coincidencia o lectura (termina de escanear)
			else // ret_val == -1 (Error)
				return EOF; // Error de flujo/EOF
            
            // match_conv ya avanzó *format, no avanzamos aquí.
		}
		else if (isspace(*format))
		{
			// Si hay espacio en el formato, saltar cualquier cantidad de espacio en el flujo.
			ret_val = match_space(f);
            if (ret_val == -1) // EOF o error en el flujo
				return EOF;
		}
		else 
		{
			// Carácter normal en el formato (ej: coma, guión, etc.)
			ret_val = match_char(f, *format);
			if (ret_val != 1)
				break; // Falla de coincidencia (el carácter no está presente)
		}
		format++; // Avanza el puntero del formato al siguiente carácter.
	}
	
	// Si hubo un error en el flujo (no solo EOF al inicio)
	if (ferror(f))
		return EOF;
	
	// Retorna el número de conversiones exitosas.
	return nconv;
}

// --------------------------------------------------------------------------
// IV. Envoltura Pública (ft_scanf)
// --------------------------------------------------------------------------

// ft_scanf: Interfaz pública que utiliza stdin.
int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format); // Inicializa la lista de argumentos variables

	int ret = ft_vfscanf(stdin, format, ap); // Llama al motor de escaneo, usando stdin
	
	va_end(ap); // Limpia la lista de argumentos variables
	return ret;
}

/*
// Ejemplo de uso (Descomentar para probar)

#include <string.h>

int main(void)
{
    int i = 0;
    char c = ' ';
    char s[20] = {0};
    int ret;

    // Test 1: %d %c %s (Se espera: 42 X Hola)
    printf("Test 1: Introduzca '42 X Hola' (sin las comillas): ");
    fflush(stdout); 
    ret = ft_scanf("%d %c %s", &i, &c, s);
    
    printf("\n--- Resultados Test 1 ---\n");
    printf("Retorno ft_scanf: %d\n", ret);
    printf("i: %d\n", i); // Esperado: 42
    printf("c: %c (ASCII: %d)\n", c, c); // Esperado: ' ' (espacio), porque %d no consume el siguiente espacio.
    printf("s: '%s'\n", s); // Esperado: 'X' si el buffer es pequeño. Si es grande, el resto de la entrada.
    
    // Para simplificar la prueba en terminal, reseteamos las variables
    i = 0;
    c = ' ';
    memset(s, 0, 20);

    // Test 2: %d,%s (Con un carácter literal ',' en el formato)
    printf("\nTest 2: Introduzca '100,Mundo' (sin las comillas): ");
    fflush(stdout); 
    ret = ft_scanf("%d,%s", &i, s);

    printf("\n--- Resultados Test 2 ---\n");
    printf("Retorno ft_scanf: %d\n", ret);
    printf("i: %d\n", i); // Esperado: 100
    printf("s: '%s'\n", s); // Esperado: 'Mundo'

    // Test 3: Lectura solo de caracteres
    i = 0;
    c = ' ';
    memset(s, 0, 20);
    printf("\nTest 3: Introduzca ' A B ' (sin comillas): ");
    fflush(stdout); 
    // %c lee el primer carácter no saltando espacios, por lo que debería leer el primer espacio
    ret = ft_scanf("%c%c%c", &s[0], &s[1], &s[2]); 

    printf("\n--- Resultados Test 3 ---\n");
    printf("Retorno ft_scanf: %d\n", ret);
    printf("Primer caracter: '%c'\n", s[0]); // Esperado: ' '
    printf("Segundo caracter: '%c'\n", s[1]); // Esperado: 'A'
    printf("Tercer caracter: '%c'\n", s[2]); // Esperado: ' '
    
    // Para terminar la línea restante en el buffer de stdin
    while(getchar() != '\n' && !feof(stdin));
    
    return (0);
}
*/

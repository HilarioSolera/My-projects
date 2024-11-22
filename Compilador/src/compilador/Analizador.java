package compilador;

import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Analizador {

    private BufferedReader reader; // Lector del archivo
    private Set<String> variablesDefinidas = new HashSet<>();
    private BufferedWriter writer; // Escritor del archivo de errores
    private Set<String> variablesDeclaradas = new HashSet<>();
    private BufferedWriter readmeWriter; // Escritor del archivo README
    private List<String> errores = new ArrayList<>(); // Lista para almacenar errores
    private Set<String> funcionesDefinidas = new HashSet<>();
    private boolean bloqueWhileAbierto = false; // Flag para saber si hay un bloque 'while' abierto
    private int indentacionWhile = 0; // Indentación del 'while' abierto
    private List<String> lineasDeCodigo = new ArrayList<>();
    private boolean enFuncion = false;  // Estado para saber si estamos dentro de una función
    private Map<String, Integer> contadorOperadoresComparacion = new HashMap<>(); // Mapa para operadores de comparación 
    private int contadorComentarios = 0; // Contador de líneas de comentario
    private Map<String, Integer> contadorTokens = new HashMap<>(); // Mapa para contar tokens
    private int errorCounter = 100; // Contador de errores, inicia en 100
    public Analizador(BufferedReader reader, BufferedWriter writer, BufferedWriter readmeWriter) {
        this.reader = reader; // Inicializa lector
        this.writer = writer; // Inicializa escritor
        this.readmeWriter = readmeWriter; // Inicializa escritor de README
    }

    public void procesarArchivo() throws IOException {
        String linea;
        int numeroLinea = 0; // Contador de líneas

        while ((linea = reader.readLine()) != null) { // Lee cada línea del archivo
            numeroLinea++;
            procesarLinea(linea, numeroLinea); // Procesa cada línea

            lineasDeCodigo.add(numeroLinea + "  " + linea + "\n");

        }

        // Escribe resumen y errores al final
        escribirResumen();
        escribirErroresAlFinal();
        generarReadMe(); // Genera un archivo README con instrucciones
    }

    private void procesarLinea(String linea, int numeroLinea) throws IOException {
        if (linea.trim().isEmpty()) { // Si la línea está vacía
            writer.write(String.format("%03d %s", numeroLinea, linea)); // Escribe la línea vacía
            writer.newLine();
            return;
        }

        String regexAsignacion = "(\\w+)\\s*=\\s*.*";
        Matcher matcher = Pattern.compile(regexAsignacion).matcher(linea);

        // Si encontramos una asignación, registramos la variable
        while (matcher.find()) {
            String variable = matcher.group(1);
            registrarVariableDefinida(variable); // Registramos la variable
        }

        String lineaConNumeracion = String.format("%03d %s", numeroLinea, linea); // Agrega numeración
        writer.write(lineaConNumeracion + "\n");

        // Verifica y cuenta comentarios
        contarComentarios(linea);

        Set<String> erroresPorLinea = new HashSet<>(); // Conjunto para errores de la línea

        // Validaciones para errores en la línea
        validarImport(linea, erroresPorLinea, numeroLinea); // Verifica posición de importaciones
        validarPrint(linea, numeroLinea, erroresPorLinea); // Valida la salida de datos con print
        validarFunciones(linea, numeroLinea, erroresPorLinea); // Valida la estructura de funciones
        validarIdentificadores(linea, numeroLinea, erroresPorLinea); // Valida identificadores
        validarSintaxisInput(linea, numeroLinea, erroresPorLinea); // Valida sintaxis de input
        validarWhile(linea, numeroLinea, erroresPorLinea); // Valida sintaxis de while
        validarLlamadoFunciones(linea, numeroLinea, erroresPorLinea); // LLAMA LA FUNCIÓN validarLlamadoFunciones
        detectarManejoErrores(linea, numeroLinea, erroresPorLinea); // Llama a la función de detección de manejo de errores

        // Agrega errores encontrados en la línea a la lista general
        errores.addAll(erroresPorLinea);
        contarTokensComparacion(linea); // Contar tokens en la línea
    }
    
    
private void validarWhile(String linea, int numeroLinea, Set<String> erroresPorLinea) {
    String lineaSinComentario = linea.split("#")[0].trim();  // Eliminamos lo que está después de '#'

    // Verificar si la línea contiene un 'while'
    if (lineaSinComentario.startsWith("while")) {
        // Verificar que la línea termine con ':'
        if (!lineaSinComentario.endsWith(":")) {
            erroresPorLinea.add("Error 003. Línea " + numeroLinea + ": Se esperaba ':' al final de la declaración del 'while'. " +
                                 "En Python, los bucles 'while' deben terminar con un colon (':') para indicar el inicio del bloque de código.");
        }

        // Verificar que después de 'while' haya una condición no vacía
        String condicion = lineaSinComentario.substring(5).split(":")[0].trim();  // Extraer la condición
        if (condicion.isEmpty()) {
            erroresPorLinea.add("Error 002. Línea " + numeroLinea + ": La condición después de 'while' no puede estar vacía. " +
                                 "El bucle 'while' requiere una expresión booleana que se evalúe como verdadera o falsa, como 'x < 5' o 'True'.");
        }

        // Verificar si la condición parece válida (si tiene caracteres de una condición booleana)
        if (!esCondicionValida(condicion)) {
            erroresPorLinea.add("Error 004. Línea " + numeroLinea + ": La condición del 'while' no es válida: '" + condicion + "'. " +
                                 "La condición debe ser una expresión booleana válida, como 'True', 'False' o una comparación, por ejemplo, 'x < 5'.");
        }

        // Verificar la indentación de la línea siguiente (bloque dentro del while)
        if (numeroLinea + 1 < lineasDeCodigo.size()) {
            String siguienteLinea = lineasDeCodigo.get(numeroLinea + 1).trim();  // Línea siguiente al 'while'
            int espacios = contarEspacios(siguienteLinea);
            if (espacios < 4) {
                erroresPorLinea.add("Error 205. Línea " + (numeroLinea + 1) + ": Error de indentación: se espera un bloque indentado con al menos 4 espacios después de la declaración del 'while'. " +
                                     "El bloque de código dentro de un 'while' debe estar indentado para indicar que forma parte de este bucle.");
            }
        }

        // Validar la indentación dentro del bloque 'while'
        int indentacionWhile = obtenerNivelIndentacion(linea);  // Obtener la indentación del 'while'

        // Recorremos las líneas siguientes para asegurarnos de que están correctamente indentadas dentro del bloque 'while'
        for (int i = numeroLinea + 1; i < lineasDeCodigo.size(); i++) {
            String siguienteLinea = lineasDeCodigo.get(i).trim();
            int indentacionSiguiente = contarEspacios(siguienteLinea);

            // Si encontramos una línea con menos indentación que el 'while', asumimos que salimos del bloque
            if (indentacionSiguiente < indentacionWhile) {
                break; // Fin del bloque 'while'
            }

            // Si la línea dentro del bloque 'while' tiene menos de 4 espacios de indentación, se marca un error
            if (indentacionSiguiente < indentacionWhile + 4) {
                erroresPorLinea.add("Error 205. Línea " + (i + 1) + ": Error de indentación: se espera un bloque indentado con al menos 4 espacios dentro del bloque 'while'. " +
                                     "Dentro de un bucle 'while', cada línea de código debe estar correctamente indentada para indicar que forma parte del bloque.");
            }
        }
    }
}
// Método auxiliar para contar los espacios al principio de una línea
// Método auxiliar para obtener el nivel de indentación de una línea



// Método auxiliar para verificar si una condición es válida en un 'while'
private boolean esCondicionValida(String condicion) {
    // Comprobamos si la condición es una de las más comunes y simples
    // En este caso, simplemente aseguramos que sea algo como True, False, x < y, etc.
    
    // Condiciones más sencillas: True, False
    if (condicion.equals("True") || condicion.equals("False")) {
        return true;
    }

    // Si la condición es más compleja (como una comparación), la validamos parcialmente
    // Verificamos si la condición tiene operadores lógicos comunes.
    if (condicion.contains("<") || condicion.contains(">") || condicion.contains("==") || condicion.contains("!=")) {
        return true;
    }

    // Si no contiene ninguna de las anteriores, lo consideramos no válido.
    return false;
}




// Función auxiliar para obtener el nivel de indentación de una línea
private int obtenerNivelIndentacion(String linea) {
    int indentacion = 0;
    // Suponemos que la indentación es con espacios. Para tabuladores, se debe ajustar si es necesario.
    while (indentacion < linea.length() && linea.charAt(indentacion) == ' ') {
        indentacion++;
    }
    return indentacion;
}

    private void contarComentarios(String linea) {
        // Verifica si la línea contiene un comentario
        if (linea.contains("#")) {
            contadorComentarios++; // Incrementa el contador de comentarios
        }
    }

    private void contarTokensComparacion(String linea) {
        String[] operadoresComparacion = {"==", "!=", "<", ">", "<=", ">="}; // Lista de operadores de comparación

        for (String operador : operadoresComparacion) { // Recorre cada operador
            if (linea.contains(operador)) { // Si la línea contiene el operador
                contadorOperadoresComparacion.put(operador, contadorOperadoresComparacion.getOrDefault(operador, 0) + 1); // Cuenta el operador
            }
        }
    }

    private void validarImport(String linea, Set<String> erroresPorLinea, int numeroLinea) {
        // Verifica si la línea contiene una declaración 'import' o 'from'
        if (linea.startsWith("import") || linea.startsWith("from")) {
            // Verifica que la línea de importación no esté en la primera línea
            if (numeroLinea > 1) {
                // Si el import no está al inicio, marca un error
                if (!erroresPorLinea.contains("import_position")) {
                    erroresPorLinea.add(String.format("Error 101. Línea %03d: La declaración 'import' debe estar al inicio del archivo. Mueve esta línea a la parte superior.", numeroLinea));
                }
            }
        }
    }

    private void escribirResumen() throws IOException {
        writer.write("\n" + contadorComentarios + " líneas de comentario\n"); // Escribe el número de comentarios
        for (Map.Entry<String, Integer> entry : contadorTokens.entrySet()) {
            writer.write(entry.getValue() + " Token " + entry.getKey() + "\n"); // Escribe resumen de tokens
        }
        escribirOperadoresComparacion(); // Escribir resumen de operadores de comparación
    }

    private void escribirOperadoresComparacion() throws IOException {
        writer.write("\nCantidad de tokens de operadores de comparación:\n"); // Escribe encabezado
        for (Map.Entry<String, Integer> entry : contadorOperadoresComparacion.entrySet()) {
            writer.write(entry.getValue() + " Token " + entry.getKey() + "\n"); // Escribe el conteo de cada operador
        }
    }

    private void escribirErroresAlFinal() throws IOException {
        if (!errores.isEmpty()) { // Si hay errores
            writer.write("\nErrores encontrados:\n");
            for (String error : errores) {
                writer.write(error + "\n"); // Escribe cada error
            }
        } else {
            writer.write("\nNo se encontraron errores.\n"); // Mensaje si no hay errores
        }
    }

    private void validarIdentificadores(String linea, int numeroLinea, Set<String> erroresPorLinea) {
        if (linea.contains("=") && !linea.contains("==")) { // Si hay asignación
            String[] partes = linea.split("=", 2); // Divide la línea
            String izquierda = partes[0].trim();

            if (izquierda.contains(",")) { // Si hay múltiples identificadores
                String[] identificadores = izquierda.split(",");
                for (String identificador : identificadores) {
                    validarIdentificador(identificador.trim(), numeroLinea, erroresPorLinea);
                }
            } else {
                validarIdentificador(izquierda, numeroLinea, erroresPorLinea); // Valida un solo identificador
            }
        }
    }

    private void validarIdentificador(String identificador, int numeroLinea, Set<String> erroresPorLinea) {
        // Verifica identificadores con caracteres no permitidos
        if (identificador.contains("[") || identificador.contains("]") || identificador.contains("(") || identificador.contains(")")) {
            return; // Ignora identificadores con estructuras complejas
        }

        // Verifica si el identificador es una palabra reservada
        if (esPalabraReservada(identificador)) {
            erroresPorLinea.add(String.format("Error 102. Línea %03d: El identificador '%s' es una palabra reservada y no puede ser utilizado como identificador.", numeroLinea, identificador));
        } else if (!identificador.matches("[a-zA-Z_][a-zA-Z0-9_]*")) { // Valida el formato del identificador
            erroresPorLinea.add(String.format("Error 103. Línea %03d: El identificador '%s' tiene un formato inválido. Asegúrate de que comience con una letra o guion bajo y contenga solo letras, números o guiones bajos.", numeroLinea, identificador));
        }
    }

    private int contarCaracter(String linea, char caracter) {
        // Cuenta cuántas veces aparece un carácter en una línea
        int contador = 0;
        for (char c : linea.toCharArray()) {
            if (c == caracter) {
                contador++;
            }
        }
        return contador;
    }

    public void validarPrint(String linea, int numeroLinea, Set<String> erroresPorLinea) {
        // Expresión regular para detectar la llamada a print con paréntesis
        String regexPrint = "\\bprint\\s*\\((.*?)\\)";
        Matcher matcher = Pattern.compile(regexPrint).matcher(linea);

        boolean tieneErrores = false; // Indicador de si se encontraron errores en la línea

        // Solo procesar la línea si contiene una llamada a print
        while (matcher.find()) {
            // Obtener el contenido dentro de los paréntesis
            String contenido = matcher.group(1).trim();

            // Verificar la posición de los paréntesis
            int indexAbre = linea.indexOf("(");
            int indexCierra = linea.indexOf(")");

            // Asegurarse de que el paréntesis de cierre viene después del de apertura
            if (indexAbre == -1 || indexCierra == -1 || indexAbre > indexCierra) {
                erroresPorLinea.add(String.format("Error 112. Línea %03d: La llamada a print() tiene paréntesis no balanceados.", numeroLinea));
                tieneErrores = true; // Se encontró un error
            }

            // Validar excepciones que no deben ser verificadas (f-strings o end="")
            if (linea.contains("print(f") || linea.contains("end=")) {
                erroresPorLinea.add(String.format("Error 117. Línea %03d: Uso no permitido de print() con f-strings o 'end'.", numeroLinea));
                tieneErrores = true; // Se encontró un error
            }

            // Caso 1: Verificar que print tenga un texto entre comillas
            if (contenido.startsWith("\"") && contenido.endsWith("\"")) {
                // Es un texto entre comillas, lo cual es válido
                // No hacemos nada, ya que es válido
            } // Caso 2: Verificar que print esté vacío (print())
            else if (contenido.isEmpty()) {
                // Esto es válido, es un salto de línea, no hacemos nada
            } // Caso 3: Verificar que print contenga una variable definida
            else if (esVariableDefinida(contenido)) {
                // La variable está definida, es válida
                // No hacemos nada, ya que es válido
            } // Caso 4: Si la variable no está definida o hay una expresión no válida, se marca como error
            else {
                // Reportamos que la sintaxis es incorrecta
                erroresPorLinea.add(String.format("Error 113. Línea %03d: Sintaxis incorrecta en la llamada a print().", numeroLinea));
                tieneErrores = true; // Se encontró un error
            }
        }

        // Verificar si existe un uso incorrecto de print sin paréntesis
        if (linea.matches(".*\\bprint\\s+[^\\(].*")) {
            erroresPorLinea.add(String.format("Error 116. Línea %03d: La llamada a print() debe tener paréntesis.", numeroLinea));
            tieneErrores = true; // Se encontró un error
        }

        // Comprobar si hay una línea que comienza con print pero que no cierra
        if (linea.contains("print(") && linea.contains("(") && !linea.contains(")")) {
            erroresPorLinea.add(String.format("Error 114. Línea %03d: Falta el paréntesis de cierre en la llamada a print().", numeroLinea));
            tieneErrores = true; // Se encontró un error
        }

        // Si no se encontró ningún error, no hacer nada
        if (!tieneErrores) {
            // No se encontraron errores, no es necesario agregar nada a erroresPorLinea
        }
    }

    // Función para verificar si una variable está definida
    private boolean esVariableDefinida(String nombreVariable) {
        // Verifica si la variable está en el conjunto de variables definidas
        // Asegúrate de que `variablesDefinidas` sea un conjunto que contiene las variables definidas
        if (variablesDefinidas.contains(nombreVariable)) {
            return true;
        }

        // Si la variable tiene subíndices, operaciones o estructuras complejas, se marca como error
        // Ejemplo: "variable[2]" o "variable + 1"
        if (nombreVariable.matches(".*[\\[\\]+\\-*/%].*")) {
            return false; // Es una expresión compleja, no permitida
        }

        // Si la variable no está definida y no es una expresión válida, la consideramos no definida
        return false;
    }

    // Función para registrar una variable como definida
    public void registrarVariableDefinida(String nombreVariable) {
        variablesDefinidas.add(nombreVariable); // Agrega la variable al conjunto de definidas
    }

    public void agregarFuncionDefinida(String linea) {
        if (!esPalabraReservada(linea)) {
            // Expresión regular para encontrar definiciones de funciones (def nombre_funcion(...))
            Pattern pattern = Pattern.compile("^\\s*def\\s+([a-zA-Z_][a-zA-Z0-9_]*)\\s*\\(.*?\\):");
            Matcher matcher = pattern.matcher(linea);

            if (matcher.find()) {
                String nombreFuncion = matcher.group(1); // Captura el nombre de la función
                funcionesDefinidas.add(nombreFuncion); // Agrega el nombre de la función a la lista

            }
        }
    }

    // Método para llenar el conjunto con los nombres de las funciones definidas
    public void validarFunciones(String linea, int numeroLinea, Set<String> erroresPorLinea) {
        String lineaSinComentario = linea.split("#")[0].trim();  // Eliminamos lo que está después de '#'

        // Verificamos si la línea comienza con 'def ', indicando la declaración de una función
        if (lineaSinComentario.startsWith("def ")) {
            // Validamos si la declaración de la función termina con ':'
            if (!lineaSinComentario.endsWith(":")) {
                erroresPorLinea.add("Error 014. Línea " + numeroLinea + ": Se esperaba ':' al final de la declaración de la función.");
            }

            // Verificamos que los paréntesis estén balanceados
            int aperturaParentesis = lineaSinComentario.indexOf('(');
            int cierreParentesis = lineaSinComentario.indexOf(')');
            if (aperturaParentesis == -1 || cierreParentesis == -1 || cierreParentesis < aperturaParentesis) {
                erroresPorLinea.add("Error 015. Línea " + numeroLinea + ": Paréntesis no balanceados en la declaración de la función.");
            }

            // Agregar la función definida a la lista de funciones (esto requiere una colección global de funciones definidas)
            String nombreFuncion = lineaSinComentario.split("\\(")[0].trim();
            funcionesDefinidas.add(nombreFuncion);

            // Verificamos la indentación de la línea siguiente, debe tener al menos 4 espacios si estamos dentro de una función
            if (numeroLinea + 1 < lineasDeCodigo.size()) {
                String siguienteLinea = lineasDeCodigo.get(numeroLinea + 1).trim();  // Línea siguiente a la función
                int espacios = contarEspacios(siguienteLinea);
                if (espacios < 4) {
                    erroresPorLinea.add("Error 205. Línea " + (numeroLinea + 1) + ": IndentationError: se espera un bloque indentado con al menos 4 espacios después de la declaración de la función.");
                }
            }

            enFuncion = true; // Marcamos que estamos dentro de una función
        } else if (enFuncion) {
            // Si estamos dentro de una función, verificamos que la indentación sea correcta
            int espacios = contarEspacios(linea);
            if (espacios < 4) {
                erroresPorLinea.add("Error 205. Línea " + numeroLinea + ": IndentationError: se espera un bloque indentado con al menos 4 espacios dentro de la función.");
            }

            // Si la indentación vuelve a 0, entonces hemos salido de la función
            if (espacios == 0) {
                enFuncion = false;
            }
        }
    }

// Función auxiliar para contar los espacios al inicio de una línea
    private int contarEspacios(String linea) {
        int espacios = 0;
        while (espacios < linea.length() && linea.charAt(espacios) == ' ') {
            espacios++;
        }
        return espacios;
    }

    // Función para validar las llamadas a funciones dentro del código
    public void validarLlamadoFunciones(String linea, int numeroLinea, Set<String> erroresPorLinea) {
        // Eliminar el comentario de la línea, si existe
        agregarFuncionDefinida(linea);
        String lineaSinComentario = linea.split("#")[0].trim();  // Eliminamos lo que está después de '#'

        // Expresión regular para detectar una llamada a función en Python
        // Permitimos espacios antes del paréntesis de apertura y después del paréntesis de cierre
        String regexLlamadoFuncion = "\\b(\\w+)\\s*\\((.*?)\\)\\s*"; // La función seguida de paréntesis, con parámetros opcionales
        Matcher matcher = Pattern.compile(regexLlamadoFuncion).matcher(lineaSinComentario); // Buscar coincidencias

        // Mientras haya coincidencias de llamada a función
        while (matcher.find()) {
            String funcionLlamada = matcher.group(1).trim(); // Obtener el nombre de la función llamada
            String parametros = matcher.group(2).trim(); // Obtener los parámetros entre paréntesis

            // Verificar si la función llamada es una palabra reservada y, si es así, ignorarla
            if (esPalabraReservada(funcionLlamada)) {
                continue; // Si es una palabra reservada, ignorar esta llamada
            }

            // Verificar que la función esté definida
            if (!getFuncionesDefinidas().contains(funcionLlamada)) {
                erroresPorLinea.add("Error 206. Línea " + numeroLinea + ": La función '" + funcionLlamada + "' no ha sido definida.");
            }

            // Verificar que la llamada tiene paréntesis correctamente balanceados
            if (!tieneParentesisBalanceados(lineaSinComentario)) {
                erroresPorLinea.add("Error 207. Línea " + numeroLinea + ": Paréntesis mal balanceados en el llamado a la función '" + funcionLlamada + "'.");
            }

            // Verificar que la llamada contiene tanto el paréntesis de apertura como el de cierre
            if (!tieneParentesisAperturaYCierre(lineaSinComentario)) {
                erroresPorLinea.add("Error 208. Línea " + numeroLinea + ": Faltan paréntesis de apertura o cierre en el llamado a la función '" + funcionLlamada + "'.");
            }

            // Validación de los parámetros: ahora consideramos también las funciones con paréntesis vacíos
            int numParametrosLlamada = contarParametros(parametros);

            // Si la función tiene parámetros, pero la cadena de parámetros está vacía (comer())
            if (parametros.isEmpty() && numParametrosLlamada > 0) {
                erroresPorLinea.add("Error 209. Línea " + numeroLinea + ": La función '" + funcionLlamada + "' tiene parámetros, pero debería estar vacía.");
            }

            // Si la función tiene paréntesis vacíos pero tiene parámetros, se genera un error
            if (!parametros.isEmpty() && numParametrosLlamada == 0) {
                erroresPorLinea.add("Error 210. Línea " + numeroLinea + ": La función '" + funcionLlamada + "' está vacía, pero debería tener parámetros.");
            }

            // Verificar que no haya espacios excesivos antes o después de los paréntesis
            if (lineaSinComentario.contains("(") && lineaSinComentario.indexOf("(") < lineaSinComentario.indexOf(funcionLlamada) + funcionLlamada.length()) {
                if (lineaSinComentario.indexOf("(") > 0 && lineaSinComentario.charAt(lineaSinComentario.indexOf("(") - 1) == ' ') {
                    erroresPorLinea.add("Error 211. Línea " + numeroLinea + ": Hay espacios antes del paréntesis de apertura en la función '" + funcionLlamada + "'.");
                }
            }

            if (lineaSinComentario.contains(")") && lineaSinComentario.lastIndexOf(")") > 0) {
                if (lineaSinComentario.charAt(lineaSinComentario.lastIndexOf(")") - 1) == ' ') {
                    erroresPorLinea.add("Error 212. Línea " + numeroLinea + ": Hay espacios después del paréntesis de cierre en la función '" + funcionLlamada + "'.");
                }
            }
        }
    }

    public Set<String> getFuncionesDefinidas() {
        return funcionesDefinidas;
    }
// Método auxiliar para contar la cantidad de parámetros en una llamada a función

    private int contarParametros(String parametros) {
        // Si no hay parámetros, el string estará vacío o tendrá solo espacios
        if (parametros.isEmpty()) {
            return 0; // Si está vacío, no hay parámetros
        }

        // Si hay parámetros, los contamos dividiendo por las comas
        String[] parametrosSeparados = parametros.split(",");
        return parametrosSeparados.length;
    }

// Método auxiliar para verificar si los paréntesis están balanceados
    private boolean tieneParentesisBalanceados(String linea) {
        int apertura = 0;
        int cierre = 0;

        // Iterar sobre cada carácter de la línea para contar los paréntesis de apertura y cierre
        for (char c : linea.toCharArray()) {
            if (c == '(') {
                apertura++;
            } else if (c == ')') {
                cierre++;
            }
        }

        // Si los paréntesis de apertura y cierre son iguales, entonces están balanceados
        return apertura == cierre;
    }

// Método auxiliar para verificar que haya tanto paréntesis de apertura como de cierre
    private boolean tieneParentesisAperturaYCierre(String linea) {
        return linea.contains("(") && linea.contains(")");
    }

// Método que verifica si el nombre es una palabra reservada
    private boolean esPalabraReservada(String nombre) {
        Set<String> palabrasReservadas = new HashSet<>(Arrays.asList(
                // Palabras reservadas
                "False", "None", "True", "and", "as", "assert", "async", "await",
                "break", "class", "continue", "def", "del", "elif", "else", "except",
                "finally", "for", "from", "global", "if", "import", "in", "is",
                "lambda", "nonlocal", "not", "or", "pass", "raise", "return",
                "try", "while", "with", "yield",
                // Funciones integradas de Python
                "abs", "all", "any", "ascii", "bin", "bool", "bytearray", "bytes",
                "callable", "chr", "classmethod", "compile", "complex", "delattr",
                "dict", "dir", "divmod", "enumerate", "eval", "exec", "filter",
                "float", "format", "frozenset", "getattr", "globals", "hasattr",
                "hash", "help", "hex", "id", "input", "int", "isinstance", "issubclass",
                "iter", "len", "list", "locals", "map", "max", "memoryview", "min",
                "next", "object", "oct", "open", "ord", "pow", "print", "property",
                "range", "repr", "reversed", "round", "set", "setattr", "slice",
                "sorted", "staticmethod", "str", "sum", "super", "tuple", "type",
                "vars", "zip",
                // Funciones comunes de módulos estándar
                "split", "choice", "randint", "shuffle", "random", "len"
        ));
        return palabrasReservadas.contains(nombre);
    }

    private void detectarManejoErrores(String linea, int numeroLinea, Set<String> erroresPorLinea) {
        // Estado de bloques
        boolean enBloqueTry = false;
        boolean enBloqueExcept = false;
        boolean contienePrintEnExcept = false;
        boolean tieneCodigoEnTry = false;
        String tipoExcepcion = "";

        // Verificar inicio de bloque 'try'
        if (linea.trim().equals("try:")) {
            enBloqueTry = true;
            tieneCodigoEnTry = false;  // Reinicia la bandera de código en try
        }

        // Detectar código dentro del bloque 'try'
        if (enBloqueTry && linea.startsWith("    ") && !linea.trim().isEmpty()) {
            tieneCodigoEnTry = true;
        }

        // Verificar inicio de bloque 'except' y tipo de excepción
        if (linea.trim().startsWith("except ")) {
            enBloqueExcept = true;
            contienePrintEnExcept = false; // Reinicia el estado de print para el nuevo bloque except

            String[] partes = linea.trim().split(" ");
            // Verificar que 'except' tenga un tipo de excepción válido
            if (partes.length > 1) {
                tipoExcepcion = partes[1].replace(":", "").trim();
                if (!esTipoExcepcionValido(tipoExcepcion)) {
                    erroresPorLinea.add("Error 220. Línea " + numeroLinea + ": Tipo de excepción no válido en el bloque except: " + tipoExcepcion);
                }
                if (!linea.trim().endsWith(":")) {
                    erroresPorLinea.add("Error 221. Línea " + numeroLinea + ": El bloque except debe terminar con dos puntos (:).");
                }
            } else {
                erroresPorLinea.add("Error 222. Línea " + numeroLinea + ": Se esperaba un tipo de excepción después de 'except'.");
            }
        }

        // Verificar la indentación dentro del bloque 'try', pero no para las líneas "try:" o "except"
        if (enBloqueTry && !linea.startsWith("    ") && !linea.trim().equals("try:") && !linea.trim().equals("except ") && !linea.trim().isEmpty()) {
            erroresPorLinea.add("Error 227. Línea " + numeroLinea + ": Las líneas dentro del bloque 'try' deben estar correctamente indentadas.");
        }

        // Verificar la indentación dentro del bloque 'except', pero no para las líneas "except"
        if (enBloqueExcept && !linea.startsWith("    ") && !linea.trim().equals("except ") && !linea.trim().isEmpty()) {
            erroresPorLinea.add("Error 228. Línea " + numeroLinea + ": Las líneas dentro del bloque 'except' deben estar correctamente indentadas.");
        }

        // Verificar si la línea después de "except" tiene un 'print'
        if (enBloqueExcept && linea.trim().startsWith("    print") && linea.trim().length() > 0) {
            contienePrintEnExcept = true; // El bloque except tiene un print
        }

        // Si se encuentra un print después de "except", no marcar error
        if (enBloqueExcept && contienePrintEnExcept) {
            // No se marca error porque el bloque except ya contiene código para manejar la excepción
            return;
        }

        // Si después de la línea "except" no hay código (como un print o cualquier otro manejo válido), marcar error
        if (enBloqueExcept && !contienePrintEnExcept && linea.trim().length() > 0 && !linea.trim().startsWith("except") && !linea.trim().startsWith("    print")) {
            erroresPorLinea.add("Error 223. Línea " + numeroLinea + ": Se esperaba un código dentro del bloque except para manejar el error (por ejemplo, un print).");
            enBloqueExcept = false; // Fin del bloque except
        }

        // Verificar que haya al menos una línea de código en el bloque 'try'
        if (enBloqueTry && !tieneCodigoEnTry && linea.trim().length() > 0) {
            erroresPorLinea.add("Error 224. Línea " + numeroLinea + ": Se esperaba código dentro del bloque 'try'.");
            enBloqueTry = false; // Fin del bloque try
        }

        // Si ya no estamos en un bloque try/except, reiniciar los estados
        if (linea.trim().equals("except") && !linea.startsWith("    ")) {
            enBloqueTry = false;
            enBloqueExcept = false;
        }
    }

// Función para verificar si el tipo de excepción es válido
    private boolean esTipoExcepcionValido(String tipoExcepcion) {
        return tipoExcepcion.equals("ArithmeticError")
                || tipoExcepcion.equals("ZeroDivisionError")
                || tipoExcepcion.equals("ValueError");
    }

    private void validarSintaxisInput(String linea, int numeroLinea, Set<String> erroresPorLinea) {
        // Verificar si la línea contiene la palabra "input"
        int indiceInput = linea.indexOf("input");
        if (indiceInput != -1) { // Si se encuentra "input"

            // Verifica que el carácter inmediatamente después de "input" sea un paréntesis de apertura '('
            if (indiceInput + 5 >= linea.length() || linea.charAt(indiceInput + 5) != '(') {
                erroresPorLinea.add(String.format("Error 106. Línea %03d: El comando 'input' debe ser seguido por un paréntesis de apertura '(' inmediatamente. Revisa la sintaxis.", numeroLinea));
                return; // Sale si hay un error
            }

            // Verifica que haya la misma cantidad de paréntesis de apertura y cierre
            int apertura = contarCaracter(linea, '(');
            int cierre = contarCaracter(linea, ')');
            if (apertura != cierre) { // Si hay desbalance de paréntesis
                erroresPorLinea.add(String.format("Error 107. Línea %03d: Desbalance de paréntesis en el comando 'input'. Asegúrate de que haya el mismo número de '(' y ')'.", numeroLinea));
            }

            // Verifica que contenga un símbolo igual '='
            int indiceIgual = linea.indexOf("=");
            if (indiceIgual == -1) {
                erroresPorLinea.add(String.format("Error 108. Línea %03d: La asignación del comando 'input' debe contener un símbolo igual '='.", numeroLinea));
            }

            // Verifica que el símbolo '=' esté antes de 'input'
            if (indiceIgual > indiceInput) {
                erroresPorLinea.add(String.format("Error 109. Línea %03d: El símbolo '=' debe estar antes del comando 'input'.", numeroLinea));
            }

            // Verifica que después de los paréntesis de apertura haya comillas dobles
            int indiceAbrirComillas = linea.indexOf("\"", indiceInput + 5); // Buscar las comillas dobles después de "("
            if (indiceAbrirComillas == -1 || indiceAbrirComillas > linea.indexOf(")", indiceInput)) {
                erroresPorLinea.add(String.format("Error 110. Línea %03d: El comando 'input' debe tener comillas dobles dentro de los paréntesis para el prompt.", numeroLinea));
            }
        }
    }

    private void generarReadMe() throws IOException {
        // Genera el archivo README.txt con instrucciones
        readmeWriter.write("Instrucciones para ejecutar el compilador:\n");
        readmeWriter.write("1. Asegúrate de tener instalado Java en tu máquina.\n");
        readmeWriter.write("2. Compila el programa en tu entorno de desarrollo (NetBeans o línea de comandos).\n");
        readmeWriter.write("3. Ejecuta el programa proporcionando el archivo Python que deseas analizar.\n");
        readmeWriter.write("4. Revisa el archivo de errores generado para cualquier problema encontrado.\n");
        readmeWriter.write("5. Observa el resumen de comentarios y tokens al final del archivo de errores.\n");
        readmeWriter.close(); // Cierra el escritor del README

    }
}

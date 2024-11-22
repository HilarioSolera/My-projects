package compilador; // Define el paquete del compilador
/*Programa realizado por Hilario David Solera Meza*/
import java.io.*; // Importa clases para manejo de entrada/salida

public class Compilador {

    private static final String EXTENSION = ".py"; // Define la extensión de archivo permitida

    public static void main(String[] args) {
        String nombreArchivo = obtenerNombreArchivo(args); // Obtiene el nombre del archivo desde argumentos
        if (nombreArchivo == null) return; // Si no es válido, termina la ejecución

        String nombreArchivoErrores = nombreArchivo.replace(EXTENSION, "-errores.log"); // Nombre del archivo de errores
        String nombreArchivoReadMe = "README.txt"; // Nombre del archivo README

        try {
            // Configuración de lectores y escritores de archivos
            BufferedReader reader = new BufferedReader(new FileReader(nombreArchivo)); // Lee el archivo de entrada
            BufferedWriter writer = new BufferedWriter(new FileWriter(nombreArchivoErrores)); // Archivo para errores
            BufferedWriter readmeWriter = new BufferedWriter(new FileWriter(nombreArchivoReadMe)); // Archivo README
            
           

            // Procesa el archivo
            Analizador analizador = new Analizador(reader, writer, readmeWriter); 
            analizador.procesarArchivo();

            // Cierra los lectores y escritores
            reader.close(); // Cierra el lector
            writer.close(); // Cierra el escritor de errores
            readmeWriter.close(); // Cierra el escritor de README

            // Mensaje final indicando la finalización del análisis
            System.out.println("Análisis completado. Errores registrados en " + nombreArchivoErrores); 

        } catch (IOException e) {
            System.out.println("Error al procesar el archivo: " + e.getMessage());
            // Imprime la traza de error
            // Manejo de excepciones
        }
    }

    private static String obtenerNombreArchivo(String[] args) {
        // Verifica si se proporcionó un argumento
        if (args.length != 1) { 
            System.out.println("Error: Se debe proporcionar un archivo .py como argumento.");
            return null; // Retorna null si no es válido
        }

        String nombreArchivo = args[0]; // Nombre del archivo pasado como argumento
        // Verifica la extensión
        
        if (!nombreArchivo.endsWith(EXTENSION)) { 
            System.out.println("Error: Solo se permiten archivos con la extensión " + EXTENSION);
            return null; // Retorna null si no es válido
        }

        return nombreArchivo; // Retorna el nombre del archivo
    }
}

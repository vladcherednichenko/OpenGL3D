package site.pixio.graphics3dx.tasks
import java.io.File

open class UpdateCMakeKt : DefaultTask() {

    init {
        group = "site.pixio"
        description = "LocalizationTask"
    }

    @TaskAction
    fun run() {
        val cppFolder = File("src/main/cpp") // Change this if your cpp folder path is different
        val cmakeFile = File("src/main/cpp/CMakeLists.txt") // Change this if your CMakeLists.txt file path is different

        if (!cppFolder.exists() || !cppFolder.isDirectory) {
            println("CPP folder does not exist or is not a directory")
            return
        }

        if (!cmakeFile.exists()) {
            println("CMakeLists.txt file does not exist")
            return
        }

        val cppFiles = cppFolder.walkTopDown()
            .filter { it.isFile && (it.extension == "cpp" || it.extension == "h") }
            .map { it.relativeTo(cppFolder).path.replace("\\", "/") }
            .toSet()

        val cmakeContent = cmakeFile.readText()
        val cmakeFiles = cmakeContent.lines()
            .filter { it.trim().startsWith("shaders/") || it.trim().endsWith(".cpp") }
            .map { it.trim().removeSuffix(")") }
            .toSet()

        val missingFiles = cppFiles - cmakeFiles

        if (missingFiles.isEmpty()) {
            println("All necessary files are included in CMakeLists.txt")
        } else {
            println("Adding missing files to CMakeLists.txt")
            val newCmakeContent = buildString {
                append(cmakeContent.substringBefore("add_library("))
                append("add_library(native-lib SHARED\n")
                cmakeFiles.forEach {
                    append("            $it\n")
                }
                missingFiles.forEach {
                    append("            $it\n")
                }
                append(")\n")
                append(cmakeContent.substringAfter("add_library(").substringAfter(")\n"))
            }
            cmakeFile.writeText(newCmakeContent)
            println("CMakeLists.txt has been updated with missing files.")
        }
    }

}

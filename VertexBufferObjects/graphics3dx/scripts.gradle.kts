import java.nio.file.Files
import java.nio.file.Path
import java.nio.file.Paths
import java.nio.file.StandardOpenOption
import java.io.File

val updateCMakeFile: () -> Unit = {
    val projectDir = Paths.get("graphics3dx/src/main/cpp/")
    val cmakeFile = projectDir.resolve("CMakeLists.txt").toFile()
    val classesDir = projectDir.resolve(".").toFile()

    val excludedFolders = listOf("Folder1", "Folder2")

    val cmakeContent = cmakeFile.readText()
    val startMarker = "# start of auto-generated source files list, do not edit"
    val endMarker = "# end of auto-generated source files list"

    val startIndex = cmakeContent.indexOf(startMarker)
    val endIndex = cmakeContent.indexOf(endMarker)

    if (startIndex == -1 || endIndex == -1) {
        throw GradleException("Markers '$startMarker' or '$endMarker' not found in CMakeLists.txt")
    }

    val cmakeBefore = cmakeContent.substring(0, startIndex + startMarker.length)
    val cmakeAfter = cmakeContent.substring(endIndex)

    fun listFilesRecursively(directory: File, excludedFolders: List<String>): List<File> {
        return directory.walkTopDown()
            .filter { file ->
                !excludedFolders.any { file.toPath().startsWith(directory.resolve(it).toPath()) }
            }
            .toList()
    }

    val cppFiles = listFilesRecursively(classesDir, excludedFolders)
        .filter { it.extension == "cpp" }
        .map { classesDir.toPath().relativize(it.toPath()).toString() }

    val hppFiles = listFilesRecursively(classesDir, excludedFolders)
        .filter { it.extension == "hpp" || it.extension == "h" }
        .map { classesDir.toPath().relativize(it.toPath()).toString() }

    val gameSource = cppFiles.joinToString(separator = "\n    ") { it }
    val gameHeader = hppFiles.joinToString(separator = "\n    ") { it }

    val middlePart = """

set(GAME_SOURCE
    $gameSource
    )

"""

    val newCMakeContent = cmakeBefore + middlePart + cmakeAfter
    cmakeFile.writeText(newCMakeContent)

    println("CMakeLists.txt updated")
}

updateCMakeFile()


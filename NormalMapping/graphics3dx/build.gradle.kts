plugins {
    id("com.android.library")
    id("org.jetbrains.kotlin.android")
}



android {


    namespace = "site.pixio.graphics3dx"

    defaultConfig {
        minSdk = 24
        compileSdk = 34
        targetSdk = 34
    }


    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }

    defaultConfig {
        externalNativeBuild {
            cmake {
                //cppFlags ""
            }
        }
    }

    externalNativeBuild {
        cmake {
            path = File("src/main/cpp/CMakeLists.txt")
        }
    }

}

dependencies {

    implementation("androidx.core:core-ktx:1.9.0")

}

tasks.preBuild {
    doFirst {}
//        val cppFolder = File("graphics3dx/src/main/cpp") // Change this if your cpp folder path is different
//        val cmakeFile = File("graphics3dx/src/main/cpp/CMakeLists.txt") // Change this if your CMakeLists.txt file path is different
//
//        if (!cppFolder.exists() || !cppFolder.isDirectory) {
//            println("CPP folder does not exist or is not a directory")
//            return@doFirst
//        }
//
//        if (!cmakeFile.exists()) {
//            println("CMakeLists.txt file does not exist")
//            return@doFirst
//        }
//
//        val cppFiles = cppFolder.walkTopDown()
//            .filter { it.isFile && (it.extension == "cpp" || it.extension == "h") }
//            .map { it.relativeTo(cppFolder).path.replace("\\", "/") }
//            .toSet()
//
//        val cmakeContent = cmakeFile.readText()
//        val cmakeFiles = cmakeContent.lines()
//            .filter { it.trim().startsWith("shaders/") || it.trim().endsWith(".cpp") }
//            .map { it.trim().removeSuffix(")") }
//            .toSet()
//
//        val missingFiles = cppFiles - cmakeFiles
//
//        if (missingFiles.isEmpty()) {
//            println("All necessary files are included in CMakeLists.txt")
//        } else {
//            println("Adding missing files to CMakeLists.txt")
//            val newCmakeContent = buildString {
//                append(cmakeContent.substringBefore("add_library("))
//                append("add_library(native-lib SHARED\n")
//                cmakeFiles.forEach {
//                    append("            $it\n")
//                }
//                missingFiles.forEach {
//                    append("            $it\n")
//                }
//                append(")\n")
//                append(cmakeContent.substringAfter("add_library(").substringAfter(")\n"))
//            }
//            cmakeFile.writeText(newCmakeContent)
//            println("CMakeLists.txt has been updated with missing files.")
//        }
//    }
}


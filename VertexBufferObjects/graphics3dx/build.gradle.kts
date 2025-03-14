plugins {
    id("com.android.library")
    id("org.jetbrains.kotlin.android")
}

apply(from = "scripts.gradle.kts")

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
                arguments ("-DANDROID_STL=c++_static")
            }
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
//            proguardFiles getDefaultProguardFile('proguard-android.txt'),
//            'proguard-rules.pro',
//            '$playcoreDir/proguard/common.pgcfg',
//            '$playcoreDir/proguard/per-feature-proguard-files'
            externalNativeBuild {
                cmake {
                    arguments ("-DANDROID_STL=c++_shared")
                }
            }
        }
        debug {
            externalNativeBuild {
                isMinifyEnabled = false
//                proguardFiles getDefaultProguardFile('proguard-android.txt'),
//                'proguard-rules.pro'
                cmake {
                    arguments ("-DANDROID_STL=c++_shared")
                }
            }
            multiDexEnabled = true
        }
    }

    externalNativeBuild {
        cmake {
            path = File("src/main/cpp/CMakeLists.txt")
        }
    }

    buildFeatures {
        prefab = true
    }

}

dependencies {

    implementation("androidx.core:core-ktx:1.9.0")
    implementation ("androidx.games:games-frame-pacing:2.1.2")

}



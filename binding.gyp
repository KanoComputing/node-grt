{
    "targets": [
        {
            "target_name": "GRT",
            "cflags_cc": ["-std=c++11", "-fexceptions", "-frtti"],
            "sources": ["src/GRT.cc", "src/NodeTimeSeriesClassificationData.cc", "src/NodeDTW.cc", "src/NodeHMM.cc", "src/NodeKMeansQuantizer.cc"],
            "include_dirs" : [
                "<!(node -e \"require('nan')\")",
 	 			"./include",
			],
            "conditions": [
                ['OS=="mac"',
                    {
                        "libraries": [
                            "<!(pwd)/lib/libgrt.a"
                        ],
                        "xcode_settings": {
                            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                            "GCC_ENABLE_CPP_RTTI": "YES",
                        },
                    }
                ],
                ['OS=="mac" and <!(node -e "console.log(parseInt(os.release()) > 15 ? 1 : 0)")',
                    {
                        "xcode_settings": {
                            "OTHER_CFLAGS": ["-std=c++11", "-stdlib=libc++"]
                        }
                    }
                ],
                ['OS=="win"',
                    {
                        "libraries": [
                            "<!(cd)/lib/grt.lib",
                        ],
                        "msvs_settings": {
                            "VCCLCompilerTool": {
                                "RuntimeTypeInfo": 'true',
                                'RuntimeLibrary': 'false',
                                "AdditionalOptions": [
                                    "/D NOMINMAX",
                                    "/D GRT_STATIC_LIB",
                                ],
                            },
                        }
                    }
                ]
            ]
        }
    ],
}

{
    "targets": [
        {
            "target_name": "NativeExtension",
            "cflags_cc": ["-std=c++11", "-fexceptions", "-frtti"],
            "sources": [ "NativeExtension.cc", "src/NodeTimeSeriesClassificationData.cc", "src/NodeDTW.cc" ],
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
                            "OTHER_CFLAGS": ["-std=c++11", "-stdlib=libc++"]
                        },
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

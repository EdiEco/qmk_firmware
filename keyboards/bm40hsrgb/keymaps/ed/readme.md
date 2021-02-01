{
	"version": "2.0.0",
	"tasks": [
        {
            "type": "npm",
            "script": "install",
            "path": "keyboards/ergodox_ez/keymaps/hacker_dvorak/",
            "problemMatcher": [],
            "label": "npm: install - keyboards/ergodox_ez/keymaps/hacker_dvorak",
            "detail": "install dependencies from package"
        },
        {
            "label": "Compile and Flash",
            "type": "shell",
            "command": "/home/edi/.local/bin/qmk",
            "args": [
                "flash"
            ],
            "problemMatcher": [],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {
            "label": "Compile",
            "type": "shell",
            "command": "/home/edi/.local/bin/qmk",
            "args": [
                "compile"
            ],
            "problemMatcher": [],
            "group": "build"
        }
    ]
}

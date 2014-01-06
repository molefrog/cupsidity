{
  "targets": [
    {
      "target_name": "binding",
      "sources": [ 
        "src/binding.cc",
        "src/dests.cc",
        "src/jobs.cc",
        "src/printing.cc"
      ],
      "link_settings": {
        "libraries": [
          "-lcups",
          "-lm"
        ]
      },
    }
  ]
}
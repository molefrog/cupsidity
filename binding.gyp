{
  "targets": [
    {
      "target_name": "binding",
      "sources": [ 
        "src/binding.cc",
        "src/dests.cc"
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
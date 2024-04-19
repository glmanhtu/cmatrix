{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc", "matrix.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}

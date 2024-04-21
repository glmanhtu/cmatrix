{
  "targets": [
    {
      "target_name": "cmatrix",
      "sources": ["cmatrix.cc", "jmatrix.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}

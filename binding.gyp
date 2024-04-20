{
  "targets": [
    {
      "target_name": "cmatrix",
      "sources": [ "cmatrix.cc", "jmatrix.cc", "SimpleMatrix.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}

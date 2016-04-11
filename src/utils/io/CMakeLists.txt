set (io_SRC
    stream.h
    stream.cc
    instance/csv.h
    instance/csv.cc
    instance/dependency.h
    instance/dependency.cc
    instance/lisp.h
    instance/lisp.cc
    dataset/block_iterator.h
    dataset/csv.h
    dataset/csv.cc
    dataset/dependency.h
    dataset/dependency.cc
    )

add_library (_zuo_io ${io_SRC})

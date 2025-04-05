# sdb

## Compiling

1. Build the docker image:

    ```text
    docker build --tag sdb .
    ```

2. Run a container from the image:

    ```text
    docker run --rm -it -v .:/sdb sdb bash
    ```

3. Run `make` within the container:

    ```text
    cd sdb
    make
    ```

Steps 2 & 3 may also be combined into a single command which will additionally exit the container:

```text
docker run --rm -v .:/sdb sdb bash -c "cd sdb && make"
```

## Validating the build

With the original x64 Linux `SuperMeatBoy` binary in the project's root directory, run:

```text
make diff
```

Alternatively, run:

```text
make diff ORIGINAL_BINARY=<path to original binary>
```

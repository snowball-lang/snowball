{
  description = "Snowball is a low-weight, statically typed, object oriented programming language. ";

  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    flake-utils,
    nixpkgs,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      packages.snowball = pkgs.stdenv.mkDerivation {
        name = "snowball";
        version = pkgs.lib.strings.readFile ./snowball.version.str;

        src = ./.;

        nativeBuildInputs = with pkgs; [cmake pkg-config makeWrapper];
        buildInputs = with pkgs; [
          zstd
          libxml2
          libsigsegv
          glib
          pcre2
          libllvm
          libbacktrace
          curl.dev
          openssl
          nlohmann_json
        ];

        patchPhase = ''
          sed -i '191i find_package(nlohmann_json REQUIRED)' CMakeLists.txt
          sed -i -e '/CPMAddPackage(/,/)/d' CMakeLists.txt
          sed -i -e '/include(FetchContent)/d' CMakeLists.txt
          sed -i -e '/FetchContent_Declare(/,/)/d' CMakeLists.txt
          sed -i -e '/FetchContent_MakeAvailable(json)/d' CMakeLists.txt
          sed -i -e 's/libcurl/curl/' CMakeLists.txt
          sed -i -e 's/app\///' app/*.cc
          sed -i -e 's/app\///' app/commands/*.h
        '';

        buildPhase = ''
          runHook preBuild

          mkdir -p bin/Release

          cmake \
            -DLLVM_ENABLE_BACKTRACES=OFF \
            -DLLVM_ENABLE_PER_TARGET_RUNTIME_DIR=OFF \
            -DLLVM_ENABLE_TERMINFO=OFF \
            -DCMAKE_OSX_ARCHITECTURES="${system}" \
            -DLLVM_ENABLE_ZLIB=OFF \
            -DLLVM_INCLUDE_EXAMPLES=OFF \
            -DLLVM_INCLUDE_DOCS=OFF \
            -DCMAKE_BUILD_TYPE=Release \
            -DEXECUTABLE_OUTPUT_PATH="bin/Release" $@ .

          cmake --build . --config Release -- -j $NIX_BUILD_CORES

          runHook postBuild
        '';
        installPhase = ''
          runHook preInstall

          install --mode +x -D ./bin/Release/snowball $out/bin/unwrapped/snowball
          install --mode +x -D ./libSnowball.so $out/lib/libSnowball.so
          install --mode +x -D ./libsnowballrt.so $out/lib/libsnowballrt.so
          cp -r $src/stdlib "$out"

          wrapProgram "$out/bin/unwrapped/snowball" --suffix LD_LIBRARY_PATH ':' "$out/lib"

          cat <<EOF > "$out/bin/snowball"
          #!/bin/sh
          if [ ! -d "\$HOME/.snowball/stdlib" ]; then
            echo -e "\x1b[32mCreating \$HOME/.snowball/stdlib\x1b[0m"
            mkdir "\$HOME/.snowball"
            cp -r "$out/stdlib"  "\$HOME/.snowball/stdlib"
          fi

          exec "$out/bin/unwrapped/snowball" \$@
          EOF

          chmod +x "$out/bin/snowball"
          runHook postInstall
        '';

        meta = {
          description = "Snowball is a low-weight, statically typed, object oriented programming language";
          homepage = "https://github.com/snowball-lang/snowball";
          license = pkgs.lib.licenses.mit;
          platforms = pkgs.lib.platforms.all;
        };
      };

      packages.default = self.packages.${system}.snowball;

      devShells.default = pkgs.mkShell {
        packages = with pkgs; [
          zstd
          libsigsegv
          cmake
          pkg-config
          glib
          pcre2
          libllvm
          libbacktrace
          libxml2
          clang-tools
          cmake-language-server
          cppcheck
          openssl
          lldb
          nlohmann_json
        ];
      };
    });
}

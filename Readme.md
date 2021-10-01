# MultiVector
I just wrapped my head around exterior algebra and wanted to do quick tests. Could not find anything other than [Versor](https://github.com/wolftype/versor) and it has a ton of cruft... plus doesn't seem to provide a path for Windows compilation. Thus I cooked this up. It supports elementary stuff up to G(3) at this point.
There are some seriously expensive (O(n^2)) stuff happening in `cleanup()` so it's not by any means optimized. However, if that is called after every operation -- as it is now -- it should always remain reasonably performant.

`vec3.hpp` is just a test class to verify your results from spinning and so on. Replace with `glm` in a serious context.
I just didn't want to drag `glm` into this already.

# Compile on Windows
(on VS command prompt)

`cl.exe main.cpp /I multivector.hpp /I vec3.hpp`

# Compile on \*nix
Seriously, I have no idea. Don't have a distro lying around...

`g++ -I./ multivector.hpp vec3.hpp main.cpp   # I guess?`

# I would like to extend this
I'd like to extend this and keep its cross-platform drag n' drop simplicity as it is meant for quick tests.

# License
MIT.

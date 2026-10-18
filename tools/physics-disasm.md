# Recovering PKPhysicsInterface from libpkphysics.so

The C++ source (`PKPhysicsInterface.C`) never made it into the repo. The only
copy is the compiled SPARC shared object `lib/libpkphysics.so`. This note shows
how the JavaScript port (`web/src/engine/physics.js`) was derived from it.

## Disassembling

```
brew install binutils
objdump -d lib/libpkphysics.so --start-address=0x2d58 --stop-address=0x3e14 > tools/libpkphysics.disasm.s
objdump -R lib/libpkphysics.so      # relocations resolve sethi/or constant loads
objdump -s -j .rodata --start-address=0x94f0 --stop-address=0x9530 lib/libpkphysics.so
```

## Constants (.rodata, big-endian IEEE doubles)

| addr   | value              | meaning                              |
|--------|--------------------|--------------------------------------|
| 0x94f0 | 1e-8               | PHYSICS_SPEED_FUDGE                  |
| 0x94f8 | 2                  | divisor for half-extents             |
| 0x9500 | 258                | screen centre x (516/2)              |
| 0x9508 | 0                  | zero                                 |
| 0x9510 | 216                | screen centre y (432/2)              |
| 0x9518 | 1.0471975333333334 | PI/3 (with PI = 3.1415926)           |
| 0x9528 | 4294967296         | 2^32 (hrtime_t -> double conversion) |

## Reconstructed C++

```cpp
void PKPhysicsInterface::update(GEGameObject* obj) {          // 0x2e20
    hrtime_t now = gethrtime();
    PKPoint p = obj->getPosition();
    hrtime_t ts = obj->getTimeStamp();
    PKVector v = obj->getVector();
    p = p + v * ((double)(now - ts) * PHYSICS_SPEED_FUDGE);
    obj->setPosition(p);
    obj->setTimeStamp(now);
}

int PKPhysicsInterface::intersect(GEGameObject* a, GEGameObject* b) { // 0x3050
    PKPoint pa = a->getPosition(), pb = b->getPosition();
    double aw = (a->getWidth()  + a->getWidthAdjust())  / 2.0;
    double bw = (b->getWidth()  + b->getWidthAdjust())  / 2.0;
    double ah = (a->getHeight() + a->getHeightAdjust()) / 2.0;
    double bh = (b->getHeight() + b->getHeightAdjust()) / 2.0;
    return pa[0]-aw < pb[0]+bw && pa[0]+aw > pb[0]-bw &&
           pa[1]-ah < pb[1]+bh && pa[1]+ah > pb[1]-bh;
}

void PKPhysicsInterface::bounceWithWall(GEGameObject* ball, GEGameObject* wall) { // 0x3508
    PKTypeID t = wall->getTypeID();
    PKVector v = ball->getVector();
    PKPoint  p = ball->getPosition();
    if (t == PK_TYPE_WALL_VERTICAL &&
        ((p[0] < 258 && v[0] < 0) || (p[0] > 258 && v[0] > 0)))
        v.setCoord(0, -v[0]);
    else if ((p[1] < 216 && v[1] < 0) || (p[1] > 216 && v[1] > 0))
        v.setCoord(1, -v[1]);
    ball->setVector(v);
}

void PKPhysicsInterface::bounceWithPlayer(GEGameObject* ball, GEGameObject* player) { // 0x38f8
    PKVector d   = ball->getPosition() - player->getPosition();
    PKVector old = ball->getVector();
    double k     = PI / 3;
    double angle = d[1] * k / (player->getHeight() / 2);   // integer division
    double speed = length(ball->getVector());
    PKVector nv(speed * cos(angle), speed * sin(angle), 0);
    if (old[0] > 0 && nv[0] > 0) nv.setCoord(0, -nv[0]);
    if (d[0]   > 0 && nv[0] < 0) nv.setCoord(0, -nv[0]);
    if (d[0]   < 0 && nv[0] > 0) nv.setCoord(0, -nv[0]);
    ball->setVector(nv);
}
```

The full disassembly is in `tools/libpkphysics.disasm.s`.

../nofuss test.ss < test.nfs
cat writeRes.ss >> test.ss
./ass test.ss
cat header.vhd > ../../WolfCoreOne/logic/src/progMem.vhd
cat test.vhd >> ../../WolfCoreOne/logic/src/progMem.vhd
cat footer.vhd >> ../../WolfCoreOne/logic/src/progMem.vhd

//===-- ObjDumper.h ---------------------------------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TOOLS_LLVM_READOBJ_OBJDUMPER_H
#define LLVM_TOOLS_LLVM_READOBJ_OBJDUMPER_H

#include <memory>
#include <system_error>

#include "llvm/ADT/StringRef.h"
#include "llvm/Object/ObjectFile.h"
#include "llvm/Support/CommandLine.h"

namespace llvm {
namespace object {
class COFFImportFile;
class ObjectFile;
}
namespace codeview {
class MergingTypeTableBuilder;
}

class ScopedPrinter;

class ObjDumper {
public:
  ObjDumper(ScopedPrinter &Writer);
  virtual ~ObjDumper();

  virtual void printFileHeaders() = 0;
  virtual void printSectionHeaders() = 0;
  virtual void printRelocations() = 0;
  virtual void printSymbols(bool PrintSymbols, bool PrintDynamicSymbols) {
    if (PrintSymbols)
      printSymbols();
    if (PrintDynamicSymbols)
      printDynamicSymbols();
  }
  virtual void printProgramHeaders(bool PrintProgramHeaders,
                                   cl::boolOrDefault PrintSectionMapping) {
    if (PrintProgramHeaders)
      printProgramHeaders();
    if (PrintSectionMapping == cl::BOU_TRUE)
      printSectionMapping();
  }

  virtual void printUnwindInfo() = 0;

  // Only implemented for ELF at this time.
  virtual void printDynamicRelocations() { }
  virtual void printDynamicTable() { }
  virtual void printNeededLibraries() { }
  virtual void printSectionAsHex(StringRef SectionName) {}
  virtual void printHashTable() { }
  virtual void printGnuHashTable() { }
  virtual void printHashSymbols() {}
  virtual void printLoadName() {}
  virtual void printVersionInfo() {}
  virtual void printGroupSections() {}
  virtual void printHashHistogram() {}
  virtual void printCGProfile() {}
  virtual void printAddrsig() {}
  virtual void printNotes() {}
  virtual void printELFLinkerOptions() {}

  // Only implemented for ARM ELF at this time.
  virtual void printAttributes() { }

  // Only implemented for MIPS ELF at this time.
  virtual void printMipsPLTGOT() { }
  virtual void printMipsABIFlags() { }
  virtual void printMipsReginfo() { }
  virtual void printMipsOptions() { }

  // Only implemented for PE/COFF.
  virtual void printCOFFImports() { }
  virtual void printCOFFExports() { }
  virtual void printCOFFDirectives() { }
  virtual void printCOFFBaseReloc() { }
  virtual void printCOFFDebugDirectory() { }
  virtual void printCOFFResources() {}
  virtual void printCOFFLoadConfig() { }
  virtual void printCodeViewDebugInfo() { }
  virtual void
  mergeCodeViewTypes(llvm::codeview::MergingTypeTableBuilder &CVIDs,
                     llvm::codeview::MergingTypeTableBuilder &CVTypes) {}

  // Only implemented for MachO.
  virtual void printMachODataInCode() { }
  virtual void printMachOVersionMin() { }
  virtual void printMachODysymtab() { }
  virtual void printMachOSegment() { }
  virtual void printMachOIndirectSymbols() { }
  virtual void printMachOLinkerOptions() { }

  virtual void printStackMap() const = 0;

  void printSectionAsString(const object::ObjectFile *Obj, StringRef SecName);
  void printSectionAsHex(const object::ObjectFile *Obj, StringRef SecName);

protected:
  ScopedPrinter &W;

private:
  virtual void printSymbols() {}
  virtual void printDynamicSymbols() {}
  virtual void printProgramHeaders() {}
  virtual void printSectionMapping() {}
};

std::error_code createCOFFDumper(const object::ObjectFile *Obj,
                                 ScopedPrinter &Writer,
                                 std::unique_ptr<ObjDumper> &Result);

std::error_code createELFDumper(const object::ObjectFile *Obj,
                                ScopedPrinter &Writer,
                                std::unique_ptr<ObjDumper> &Result);

std::error_code createMachODumper(const object::ObjectFile *Obj,
                                  ScopedPrinter &Writer,
                                  std::unique_ptr<ObjDumper> &Result);

std::error_code createWasmDumper(const object::ObjectFile *Obj,
                                 ScopedPrinter &Writer,
                                 std::unique_ptr<ObjDumper> &Result);

void dumpCOFFImportFile(const object::COFFImportFile *File,
                        ScopedPrinter &Writer);

void dumpCodeViewMergedTypes(
    ScopedPrinter &Writer, llvm::codeview::MergingTypeTableBuilder &IDTable,
    llvm::codeview::MergingTypeTableBuilder &TypeTable);

} // namespace llvm

#endif
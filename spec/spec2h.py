#!/usr/bin/env python3
from string import Template
import sys
import tomllib

# Do not look at this, do not touch this, do not work on it.
# This is a horrible script.

class SpecParser:
    def __init__(self, specfile):
        with open(specfile, "rb") as sf:
            self.toml = tomllib.load(sf)
        self.target = open(self.toml["spec"]["file"], "w")
        self.FELIS_INTERNALS = self.toml["spec"].get("FELISINTERNALS", False)
        self.specname = self.toml["spec"]["specname"]
        self.buff = ""

    def __gen_macro(self, name, value):
        self.buff += Template("#define ${NAME} ${VALUE}\n").substitute(SPECNAME=self.specname.upper(), NAME=name.upper(), VALUE=value)


    def gen(self):
        guard = Template("#ifndef __${NAME}_H__\n#define __${NAME}_H__\n\n")
        self.buff += guard.substitute(NAME=self.specname.upper())

        includes = self.toml["includes"]
        for include_file in includes:
          self.buff += Template("#include ${INCLUDE}\n").substitute(INCLUDE=include_file )
        decl = self.toml["decl"]

        if "Define" in decl:
            for macro_name, macro_info in self.toml["decl"].get("Define", {}).get("Macro", {}).items():
                val = macro_info["Value"]
                self.__gen_macro(macro_name.upper(), val)
            for fn_name, fn_info in self.toml["decl"].get("Define", {}).get("Function", {}).items():
                args = ', '.join(fn_info.get("Args", {}).keys())
                val = fn_info["Value"]
                self.buff += f"#define {self.specname.upper()}_{fn_name}({args}) {val}\n"
        # Type aliases
        if "Type" in decl:
            for typename, typedef in decl["Type"].items():
                if self.FELIS_INTERNALS:
                    t = Template("typedef $TYPE ${NAME}_t;\n")
                else:
                    t = Template("typedef $TYPE $NAME;\n")
                self.buff += t.substitute(TYPE=typedef, NAME=typename)

        # Structs
        if "Struct" in decl:
            for struct_name, struct_info in decl["Struct"].items():
                field_lines = ""
                for field_name, field_type in struct_info["Fields"].items():
                    line = Template("    $TYPE $NAME;\n").substitute(TYPE=field_type, NAME=field_name)
                    field_lines += line
                s = Template("struct $NAME {\n$FIELDS};\n\n")
                self.buff += s.substitute(NAME=struct_name, FIELDS=field_lines)

        # Enums
        if "Enum" in decl:
            for enum_name, enum_info in decl["Enum"].items():
                field_lines = ""
                if "StringMapping" in enum_info and enum_info["StringMapping"] is True:
                    for name, value in enum_info["Fields"].items():
                        self.__gen_macro(f"{enum_name}_{name}_STR", f"\"{name}\"")
                for name, value in enum_info["Fields"].items():
                    line = Template("    ${ENAME}_${NAME} = $VALUE,\n").substitute(
                        SPEC=self.specname.upper(), ENAME=enum_name.upper(), NAME=name.upper(), VALUE=value)
                    field_lines += line
                field_lines = field_lines[:-2] + "\n"
                e = Template("enum $NAME {\n$FIELDS};\n\n")
                self.buff += e.substitute(NAME=enum_name, FIELDS=field_lines)

        # Unions
        if "Union" in decl:
            for union_name, union_info in decl["Union"].items():
                field_lines = ""
                for field_name, field_type in union_info["Fields"].items():
                    line = Template("    $TYPE $NAME;\n").substitute(TYPE=field_type, NAME=field_name)
                    field_lines += line
                u = Template("union $NAME {\n$FIELDS};\n\n")
                self.buff += u.substitute(NAME=union_name, FIELDS=field_lines)
        if "Function" in decl:
            for function_name, function_info in decl["Function"].items():
              function_lines = ""
              for param_name, param_type in function_info["Params"].items():
                function_lines += Template("$TYPE $NAME,").substitute(TYPE=param_type, NAME=param_name)
              function_lines = function_lines[:-1]
              f = Template("$ATTRIBUTES $RETTYPE $NAME($PARAMS);\n")
              self.buff += f.substitute(ATTRIBUTES=function_info["Attributes"], RETTYPE=function_info["ReturnType"], NAME=function_name, PARAMS=function_lines)
        if "Emit" in decl:
            for _, emit in decl["Emit"].items():
              self.buff += emit + "\n"
        self.buff += "#endif\n"

    def wrt_buf(self):
        print(self.buff)
        self.target.write(self.buff)
        self.target.close()

def main():
    if len(sys.argv) != 2:
        print("Usage:", sys.argv[0], "<specfile>")
        return
    sp = SpecParser(sys.argv[1])
    sp.gen()
    sp.wrt_buf()

if __name__ == "__main__":
    main()
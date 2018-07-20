using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace TBuilder
{
    class Program
    {
        const string EnumerateLexem = "ENUMERATORS";
        static void Main(string[] args)
        {

            var name = "t_to_gen.json";
            FileReader reader = new FileReader();
            reader.Read(name);
            var emuns = EnumsGenerator.Generate(reader.enumerators);
            var table = TableGenerator.Generate(EnumsGenerator.arrays, "SimpleTable");
            Console.WriteLine(table);

            using (var textWriter = new StreamWriter(name + "asdas", false, Encoding.ASCII))
            {
                textWriter.WriteLine(emuns);
                textWriter.WriteLine(table);
            }

        }
        public class FileReader
        {
            public void Read(string fileName)
            {
                string text = "";
                using (var textReader = new StreamReader(fileName))
                {
                    text = textReader.ReadToEnd();
                }

                JsonTextReader reader = new JsonTextReader(new StringReader(text));
                while (reader.Read())
                {
                    if (reader.Value != null)
                    {
                        if (reader.Path.Contains(EnumerateLexem))
                        {
                            CheckEnumerators(enumerators, reader);
                        }
                    }
                }
                foreach (var enumerator in enumerators)
                {
                    if (enumerator.EnumValues.Count > 0)
                    {
                        enumerator.Regtype = enumerator.EnumValues[0];
                        enumerator.EnumValues.Remove(enumerator.EnumValues[0]);
                    }
                }
            }
            private void CheckEnumerators(List<RegsEnumerator> enumerators, JsonTextReader reader)
            {
                if (reader.Path.Contains(EnumerateLexem) && !reader.Path.Contains("[") && reader.Path.Contains("."))
                {
                    var newEnum = new RegsEnumerator()
                    {
                        EnumName = reader.Value.ToString()
                    };
                    if (reader.Path.Contains("RO"))
                    {
                        newEnum.AccesType = "RO";
                    }

                    if (reader.Path.Contains("WO"))
                    {
                        newEnum.AccesType = "WO";
                    }
                    enumerators.Add(newEnum);
                }
                foreach (var enumerator in enumerators)
                {
                    if (reader.Path.Contains(enumerator.EnumName) && reader.Path.Contains("["))
                    {
                        enumerator.EnumValues.Add(reader.Value.ToString());
                    }
                }
            }
            public List<RegsEnumerator> enumerators = new List<RegsEnumerator>();

        }
        public class RegsEnumerator
        {
            public string EnumName = "";
            public string Regtype = "";
            public string AccesType = "";
            public List<string> EnumValues = new List<string>();
        }

        //enum class Name { val_1 = 0, val_2 = 1, val_3 = 2, val_4 = 4 };
        public static class EnumsGenerator
        {
            public static string Generate(List<RegsEnumerator> enumerators)
            {
                string result = "";
                foreach (var enumerator in enumerators)
                {
                    RegsArray array = new RegsArray();
                    array.ArrayName = "m_" + enumerator.EnumName.ToLower() + "_gen";
                    array.AccType = enumerator.AccesType;
                    array.Type = enumerator.Regtype;
                    array.MinValInTotalArray = AddressCounter;
                    result += "\nenum class " + enumerator.EnumName + "\n{\n";
                    array.EnumName = enumerator.EnumName;
                    foreach (var name in enumerator.EnumValues)
                    {
                        Reg newReg = new Reg();
                        newReg.Address = AddressCounter.ToString();
                        result += "\t" + name + " = " + AddressCounter + ",\n";
                        AddressCounter++;
                        array.regs.Add(newReg);

                    }
                    array.MaxValInTotalArray = AddressCounter - 1;
                    array.Len = array.MaxValInTotalArray - array.MinValInTotalArray + 1;
                    result += "};\n";
                    arrays.Add(array);
                }
                return result;
            }
            public static uint AddressCounter = 0;
            public static List<RegsArray> arrays = new List<RegsArray>();
        }

        public class RegsArray
        {
            public string ArrayName = "";
            public string Type = "";
            public uint MaxValInTotalArray = 0;
            public uint MinValInTotalArray = 0;
            public uint Len = 0;
            public string AccType = "";
            public string EnumName = "";
            public List<Reg> regs = new List<Reg>();
        }
        public class Reg
        {
            public string Address = "";
        }

        public static class TableGenerator
        {
            public static string Generate(List<RegsArray> arrays, string className)
            {
                string result = "\nclass " + className + "\n" +
                                  "{\n" +
                                  "    public: \n";

                // getters def
                foreach(var array in arrays)
                {
                    string getterName = "getReg";
                    //if (array.AccType == "RO") getterName = "getRoReg";
                    //if (array.AccType == "WO") getterName = "getWoReg";
                    string def = "        " + array.Type + " & " + getterName + "("+ array.EnumName + " addr)\n" +
                                 "        {\n" +
                                 "            return " + array.ArrayName + "[static_cast<uint32_t>(addr) - " + array.MinValInTotalArray + "];\n" +
                                 "        }\n"             ;
                    result += def;
                }
                result += "\n    private:\n";

                foreach (var array in arrays)
                {
                    
                    // arrays def
                    string def = "        " + array.Type + " " + array.ArrayName + "[" + array.Len + "] = { ";
                    int defLen = def.Length;
                    foreach (var reg in array.regs)
                    {
                        string regDef = "";
                        if (array.regs[0].Address != reg.Address)
                        {
                            for (int i = 0; i < defLen ; i++)
                            {
                                regDef += " ";
                            }
                        }
                        regDef += array.Type + "(" + reg.Address + ", " + "RegAccessType::" + array.AccType + ")";
                        if (array.regs[array.regs.Count - 1].Address != reg.Address)
                        {
                            regDef += ",\n";
                        }
                        else
                        {
                            regDef += " };\n\n";
                        }
                        def += regDef;
                    }
                    result += def ;
                }
                result += "};";
                return result;
            }
        }
    }
}

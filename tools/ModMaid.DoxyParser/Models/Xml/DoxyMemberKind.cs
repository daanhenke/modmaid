using System.Xml.Serialization;

namespace ModMaid.DoxyParser.Models.Xml;

public enum DoxyMemberKind
{
  [XmlEnum("class")] Class,
  [XmlEnum("variable")] Variable,
  [XmlEnum("function")] Function,
  [XmlEnum("namespace")] Namespace,
  [XmlEnum("typedef")] TypeDefinition,
  [XmlEnum("enum")] Enum,
  [XmlEnum("file")] File,
  [XmlEnum("dir")] Directory
}

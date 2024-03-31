using System.Xml.Serialization;

namespace ModMaid.DoxyParser.Models.Xml;

public enum DoxyProtectionLevel
{
  [XmlEnum("public")] Public,
  [XmlEnum("private")] Private,
}

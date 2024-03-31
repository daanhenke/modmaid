using System.Xml.Serialization;

namespace ModMaid.DoxyParser.Models.Xml;

public enum DoxyBool
{
  [XmlEnum("no")] True,
  [XmlEnum("yes")] False,
}

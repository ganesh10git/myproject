<?php
class XWIKIParser {
	private $patterns, $replacements;

	public function __construct($analyze=false) {
		$this->patterns=array(
			// Headings
			"/^=== (.+?) ===$/m",						// Subheading
			"/^== (.+?) ==$/m",						// Heading
			"/\_\_(.+?)\_\_/s",						// underline
			"/\-\-\-\-(.+?)\n/s",				// horizontal line
			"/\-\-(.+?)\-\-/s",						// strike
			"/\^\^(.+?)\^\^/s",						// sup-script
			"/\,\,(.+?)\,\,/s",						// sub-script
			"/\*\*(.+?)\*\*/s",						// Bold
			"/\/\/(.+?)\/\//s",						// Italic
						
			// Ordered list
			"/[\n\r]?#.+([\n|\r]#.+)+/",					// First pass, finding all blocks
			"/[\n\r]#(?!#) *(.+)(([\n\r]#{2,}.+)+)/",			// List item with sub items of 2 or more
			"/[\n\r]#{2}(?!#) *(.+)(([\n\r]#{3,}.+)+)/",			// List item with sub items of 3 or more
			"/[\n\r]#{3}(?!#) *(.+)(([\n\r]#{4,}.+)+)/",			// List item with sub items of 4 or more
			// Unordered list
			"/[\n\r]?\*.+([\n|\r]\*.+)+/",					// First pass, finding all blocks
			"/[\n\r]\*(?!\*) *(.+)(([\n\r]\*{2,}.+)+)/",			// List item with sub items of 2 or more
			"/[\n\r]\*{2}(?!\*) *(.+)(([\n\r]\*{3,}.+)+)/",			// List item with sub items of 3 or more
			"/[\n\r]\*{3}(?!\*) *(.+)(([\n\r]\*{4,}.+)+)/",			// List item with sub items of 4 or more
			
			// List items
			"/^[#\*]+ *(.+)$/m",						// Wraps all list items to <li/>
	
		);
		$this->replacements=array(
			// Headings
			"<h3>$1</h3>",
			"<h2>$1</h2>",
			"<u>$1</u>",
			"<hr>$1</hr>",
			"<strike>$1</strike>",
			"<sup>$1</sup>",
			"<sub>$1</sub>",
			"<strong>$1</strong>",
			"<em>$1</em>",
			// Ordered list
			"\n<ol>\n$0\n</ol>",
			"\n<li>$1\n<ol>$2\n</ol>\n</li>",
			"\n<li>$1\n<ol>$2\n</ol>\n</li>",
			"\n<li>$1\n<ol>$2\n</ol>\n</li>",
			// Unordered list
			"\n<ul>\n$0\n</ul>",
			"\n<li>$1\n<ul>$2\n</ul>\n</li>",
			"\n<li>$1\n<ul>$2\n</ul>\n</li>",
			"\n<li>$1\n<ul>$2\n</ul>\n</li>",
			// List items
			"<li>$1</li>",
			
		
		);
		if($analyze) {
			foreach($this->patterns as $k=>$v) {
				$this->patterns[$k].="S";
			}
		}
	}
	public function parse($input) {
		if(!empty($input))
			$output=preg_replace($this->patterns,$this->replacements,$input);
		else
			$output=false;
		return $output;
	}
}

var Module = {
	preRun: function() {
		var in_code_buf = [];
		var term = new Terminal({
			cols: 80,
			rows: 20,
			useStyle: true
		});

		function stdin() {
			if (in_code_buf.length == 0)
				return null;
			else
				return in_code_buf.shift();
		}
		function stdout(code) {
			term.write(String.fromCharCode(code));
		}
		function stderr(code) {
			term.write(String.fromCharCode(code));
		}

		var loadingElement = document.getElementById('loading');
		if (loadingElement)
			loadingElement.style.display = 'none';

		term.open(document.getElementById('stdio'));
		term.reset();
		term.on('data', function(data) {
			in_code_buf.push(data.charCodeAt(0) | 0);
		});

		FS.init(stdin, stdout, stderr);
	}
};
